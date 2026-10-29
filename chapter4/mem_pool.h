#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "macros.h"

namespace Common {
	template<typename T>
	class MemPool final {
	public:
		explicit MemPool(std::size_t num_elems) :
			store_(num_elems, {T(), true}) {
		ASSERT(reinterpret_cast<const ObjectBlock *>(&(store_[0].object_)) == &(store_[0]),"T object should be first member of ObjectBlock.");
		}

		template<typename... Args>
		T *allocate(Args... args) noexcept {
			auto obj_block = &(store_[next_free_index_]);
			ASSERT(obj_block->is_free_, "Expected free ObjectBlock at index:" + std::to_string(next_free_index_));

			T *ret = &(obj_block->object_);
			// = new T(args...); alternative inneficient approach that uses dynamic memory allocation.
			ret = new(ret) T(args...); // deliberately choosing to save the new args inside the place we want (obj_block->object_)
			// the technique above is called placement new

			obj_block->is_free_ = false; // after storing the object, we assure that space is occupied.

			// update next free index now
			updateNextFreeIndex();

			return ret; // return pointer to that object in memory (it's inside the store range of memory = memory pool)
		}

	private:
		auto updateNextFreeIndex() noexcept {
			const auto initial_free_index = next_free_index_;
			while(!store_[next_free_index_].is_free_) {
				++next_free_index_;
				if (next_free_index_ == store_.size()) [[unlikely]] {
					// instead of expanding the memory pool
					// it's a best practice to turnaround and begin from 0th index in store_
					next_free_index_ = 0;
				}

				if (initial_free_index == next_free_index_) [[unlikely]] {
					ASSERT(initial_free_index != next_free_index_, "Memory Pool out of space");
				}
			}
		}

		struct ObjectBlock {
			T object_;
			bool is_free_ = true; // the semantic intent of the object
		};

		std::vector<ObjectBlock> store_; // custom mempool in the heap

		// size_t is the default choice for any OS and architecture.
		size_t next_free_index_ = 0;
		};
}
