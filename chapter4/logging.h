#pragma once

#include <string>
#include <fstream>
#include <cstdio>

#include "macros.h"
#include "lf_queue.h"
#include "thread_utils.h"
#include "time_utils.h"

namespace Common {
  constexpr size_t LOG_QUEUE_SIZE = 8 * 1024 * 1024; // 8MB

  enum class LogType : int8_t {
    CHAR = 0,
    INTEGER = 1,
    LONG_INTEGER = 2,
    LONG_LONG_INTEGER = 3,
    UNSIGNED_INTEGER = 4,
    UNSIGNED_LONG_INTEGER = 5,
    UNSIGNED_LONG_LONG_INTEGER = 6,
    FLOAT = 7,
    DOUBLE = 8
  };

  // This structure contains a member of type LogType to specify the type of value it holds. The other member in this 
  // structure is a union of the different possible primitive types
  // example: {LogType::CHAR, {.c = 'A'}} -> type and actual value.
  struct LogElement {
    LogType type_ = LogType::CHAR;
    // std::variant has worse runtime performance; hence, we choose to move forward with the old-style union
    union { // union doesn't allocate a memory space for each of its members like Struct; it only allocates for the biggest one
      char c;
      int i;
      long l;
      long long ll;
      unsigned u;
      unsigned long ul;
      unsigned long long ull;
      float f;
      double d;
    } u_;
  };

  class Logger final {
  public:
    // the flushQueue could have been defined outside of the logger class, but it would need:
    // - to receive arguments, as the parameters in the class are private
    // - have the private parameters be made public
    auto flushQueue() noexcept {
      while (running_) {
						// this condition ensure that consumer will not do anything before the producer writes,
						// as queue.size() will be 0. Next also increments only when something is written by the producer.
        for (auto next = queue_.getNextToRead(); queue_.size() && next; next = queue_.getNextToRead()) {
          switch (next->type_) {
            case LogType::CHAR:
              file_ << next->u_.c;
              break;
            case LogType::INTEGER:
              file_ << next->u_.i;
              break;
            case LogType::LONG_INTEGER:
              file_ << next->u_.l;
              break;
            case LogType::LONG_LONG_INTEGER:
              file_ << next->u_.ll;
              break;
            case LogType::UNSIGNED_INTEGER:
              file_ << next->u_.u;
              break;
            case LogType::UNSIGNED_LONG_INTEGER:
              file_ << next->u_.ul;
              break;
            case LogType::UNSIGNED_LONG_LONG_INTEGER:
              file_ << next->u_.ull;
              break;
            case LogType::FLOAT:
              file_ << next->u_.f;
              break;
            case LogType::DOUBLE:
              file_ << next->u_.d;
              break;
          }
          queue_.updateReadIndex();
        }
	// it writes to file everything that was accumulated in the buffer, as ofstream:: somehow accumulates in the buffer before
	// sending it to disk
        file_.flush();

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(10ms);
      }
    }

    // this opens a file, creates a thread, runs the consumer logging thread (reads from the lfq and adds data onto the file)
    // and cleans any cache
    explicit Logger(const std::string &file_name)
        : file_name_(file_name), queue_(LOG_QUEUE_SIZE) {
      file_.open(file_name);
      ASSERT(file_.is_open(), "Could not open log file:" + file_name);                    // this thread will empty the queue 
                                                                                          // of log data and write the data to the file
									     // anonymous fn: this = Logger class & flushQueue is called
      logger_thread_ = createAndStartThread(-1, "Common/Logger " + file_name_, [this]() { flushQueue(); });
      ASSERT(logger_thread_ != nullptr, "Failed to start Logger thread.");
    }

    // Destructor is called when the lifetime of Logger() class ends
    ~Logger() {
      std::string time_str;
      std::cerr << Common::getCurrentTimeStr(&time_str) << " Flushing and closing Logger for " << file_name_ << std::endl;

      // it waits until the queue is empty
      while (queue_.size()) {
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
      }
      running_ = false; // since queue is empty, flushQueue won't be running
      logger_thread_->join(); // wait for it to finish - 10sec, flush?

      file_.close(); // file is closed
      std::cerr << Common::getCurrentTimeStr(&time_str) << " Logger for " << file_name_ << " exiting." << std::endl;
    }

    // All these pushValue functions were implemented so that C++ can dynamically discover which fn to execute
    // One push function could have been made, but it would contain too much branch possibilities (if/else's),
    // Causing delay in our system
    auto pushValue(const LogElement &log_element) noexcept {
      *(queue_.getNextToWriteTo()) = log_element;
      queue_.updateWriteIndex();
    }

    auto pushValue(const char value) noexcept {
      pushValue(LogElement{LogType::CHAR, {.c = value}});
    }

    auto pushValue(const int value) noexcept {
      pushValue(LogElement{LogType::INTEGER, {.i = value}});
    }

    auto pushValue(const long value) noexcept {
      pushValue(LogElement{LogType::LONG_INTEGER, {.l = value}});
    }

    auto pushValue(const long long value) noexcept {
      pushValue(LogElement{LogType::LONG_LONG_INTEGER, {.ll = value}});
    }

    auto pushValue(const unsigned value) noexcept {
      pushValue(LogElement{LogType::UNSIGNED_INTEGER, {.u = value}});
    }

    auto pushValue(const unsigned long value) noexcept {
      pushValue(LogElement{LogType::UNSIGNED_LONG_INTEGER, {.ul = value}});
    }

    auto pushValue(const unsigned long long value) noexcept {
      pushValue(LogElement{LogType::UNSIGNED_LONG_LONG_INTEGER, {.ull = value}});
    }

    auto pushValue(const float value) noexcept {
      pushValue(LogElement{LogType::FLOAT, {.f = value}});
    }

    auto pushValue(const double value) noexcept {
      pushValue(LogElement{LogType::DOUBLE, {.d = value}});
    }

    auto pushValue(const char *value) noexcept {
      while (*value) {
        pushValue(*value);
        ++value;
      }
    }

    // accepts a C++ std::string (by const reference to avoid copying it)
    auto pushValue(const std::string &value) noexcept {
      pushValue(value.c_str());
    }

    // if log fn receives not only string, but also % with interpolated arguments
    template<typename T, typename... A>
    auto log(const char *s, const T &value, A... args) noexcept {
      while (*s) {
        if (*s == '%') {
          if (*(s + 1) == '%') [[unlikely]] { // to allow %% -> % escape character.
            ++s;
          } else {
            pushValue(value); // substitute % with the value specified in the arguments.
            log(s + 1, args...); // pop an argument and call self recursively.
            return;
          }
        }
        pushValue(*s++);
      }
      FATAL("extra arguments provided to log()");
    }

    // note that this is overloading not specialization. gcc does not allow inline specializations.
    // ptr to first letter's memory address; as a string is a contiguous array, string is found by just going to the next memory slot (++s)
    auto log(const char *s) noexcept {
      while (*s) {
        if (*s == '%') {
          if (*(s + 1) == '%') [[unlikely]] { // to allow %% -> % escape character.
            ++s;
          } else {
            FATAL("missing arguments to log()");
          }
        }
        pushValue(*s++);
      }
    }


  Logger() = delete;
  Logger(const Logger &) = delete;
  Logger(const Logger &&) = delete;
  Logger &operator=(const Logger &) = delete;
  Logger &operator=(const Logger &&) = delete;

  private:
    const std::string file_name_; // file name
    std::ofstream file_; // actual file where logs go

    LFQueue<LogElement> queue_; // lock-free queue that is shared between main and logging thread
    std::atomic<bool> running_ = {true}; // swith on and off
    std::thread *logger_thread_ = nullptr;
  };

}
