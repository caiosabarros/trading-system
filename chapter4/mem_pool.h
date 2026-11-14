#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "macros.h"

namespace Common {
	template<typename T>
	class MemPool final {
	public:
		// This is also the reason we made our constructor explicit 
		// – to prohibit implicit conversions where we do not expect them
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

			// the below is a pointer to the object T, not to object_block. This is why the is_free isn't shown when dereferencing the return from allocate()
			return ret; // return pointer to that object in memory (it's inside the store range of memory = memory pool)
		}

		auto deallocate(const T *elem) noexcept {
			// reinterpret_cast can be used because a pointer to a struct equals a pointer to its first element
			// elem is casted into a _const_ ObjectBlock because of the read-only nature of the _elem_
			const auto elem_index = (reinterpret_cast<const ObjectBlock *>(elem) - &store_[0]);
			// TODO: make a test to fail the assert below - get some other store and try to deallocate some object not in that store
			// The ptrs subtraction will yield a bigger number than the memory pool size, as the other object is somewhere else in memory
			ASSERT(elem_index >= 0 && static_cast<size_t>(elem_index) < store_.size(), "Element being deallocated does not belong to this Memory pool.");
			ASSERT(!store_[elem_index].is_free_, "Expected in-use ObjectBlock at index:" + std::to_string(elem_index));
			store_[elem_index].is_free_ = true;
		}


		// Deleted default, copy & move constructors and assignment-operators.
		MemPool() = delete;

		MemPool(const MemPool &) = delete;

		MemPool(const MemPool &&) = delete;

		MemPool &operator=(const MemPool &) = delete;

		MemPool &operator=(const MemPool &&) = delete;

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
