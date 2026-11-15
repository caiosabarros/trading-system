#pragma once

# include <iostream>
# include <vector>
# include <atomic>

# include "macros.h"

namespace Common {
	template<typename T>

	class LFQueue final {
	public:
		LFQueue(std::size_t num_elems) :
			store_(num_elems, T()) {
		}

		auto getNextToWriteTo() noexcept {
			return &store_[next_write_index_];
		}

		// This commit way of doing things relies on the following:
		// updateWrite is controlled by the consumer, as having more control will allow it to update (or not update) the index
		// Think of cases when only a certain byte is modified, rather than a whole new single object being overwritten, which wastes resources.
		auto updateWriteIndex() noexcept {
			// next write is always to the next (+1) within the range of vector's size.
			// it's desirable for low-latency that the vector wraps around. This ensure no new dynamic memory allocation.
			next_write_index_ = (next_write_index_ + 1) % store_.size();
			num_elements_++;
		}

		auto getNextToRead() const noexcept -> const T * {
			return (size() ? &store_[next_read_index_] : nullptr);
	    	}

		auto updateReadIndex() noexcept {
			next_read_index_ = (next_read_index_ + 1) % store_.size();
			ASSERT(num_elements_ != 0, "Read an invalid element in:" + std::to_string(pthread_self()));
			num_elements_--;
		}

		auto size() const noexcept {
			return num_elements_.load();
		}

		// Deleted default, copy & move constructors and assignment-operators.
		// explicitly deleted to ensure they are not accidentally called without the developer's knowledge.
		LFQueue() = delete;

		LFQueue(const LFQueue &) = delete;

		LFQueue(const LFQueue &&) = delete;

		LFQueue &operator=(const LFQueue &) = delete;

		LFQueue &operator=(const LFQueue &&) = delete;

	private:
		std::vector<T> store_;

		// These need to be the std::atomic<> type, since the reading and writing operations are performed from different threads.
		std::atomic<size_t> next_write_index_ = {0};
		std::atomic<size_t> next_read_index_ = {0};

		std::atomic<size_t> num_elements_ = {0};
	};
}


