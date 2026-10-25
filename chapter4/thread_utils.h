#pragma once

#include <thread>
#include <iostream>
#include <unistd.h>
#include <atomic>

namespace Common {

	  /// Set affinity for current thread to be pinned to the provided core_id.
	  inline auto setThreadCore(int core_id) noexcept {
	    cpu_set_t cpuset;

	    CPU_ZERO(&cpuset);
	    CPU_SET(core_id, &cpuset);

	    return (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) == 0);
	  }

	// a fn and its arguments
	// this is called variadic template arguments: it allows for a fn to receive
	// a fn and as many arguments as needed
	template<typename T, typename... A>
	inline auto createAndStartThread(
		int core_id, // thread identifier
		const std::string name, // constant to prevent copy
		T &&func, // double && == forwarding reference == keep every incoming var exactly as it is - no copies, no data loss
		A &&... args
	) noexcept {
		auto t = new std::thread([&]() {
			if (core_id >= 0 && !setThreadCore(core_id)) {
				std::cerr << "Failed to set affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;
				exit(EXIT_FAILURE);
			}
			std::cerr << "Set affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;

			std::forward<T>(func)((std::forward<A>(args))...);
		});

	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(1s);

	return t;

	}
}
