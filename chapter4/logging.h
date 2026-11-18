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
  }

  // This structure contains a member of type LogType to specify the type of value it holds. The other member in this 
  // structure is a union of the different possible primitive types
  struct LogElement {
    LogType type_ = LogType::CHAR;
    // std::variant has worse runtime performance; hence, we choose to move forward with the old-style union
    union {
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
    explicit Logger(const std::string &file_name)
        : file_name_(file_name), queue_(LOG_QUEUE_SIZE) {
      file_.open(file_name);
      ASSERT(file_.is_open(), "Could not open log file:" + file_name);                    // this thread will empty the queue 
                                                                                          // of log data and write the data to the file
      logger_thread_ = createAndStartThread(-1, "Common/Logger " + file_name_, [this]() { flushQueue(); });
      ASSERT(logger_thread_ != nullptr, "Failed to start Logger thread.");
    }
  private:
    const std::string file_name_; // file name
    std::ofstream file_; // actual file where logs go

    LFQueue<LogElement> queue_; // lock-free queue that is shared between main and logging thread
    std::atomic<bool> running_ = {true}; // swith on and off
    std::thread *logger_thread_ = nullptr; 
  };

  }

}
