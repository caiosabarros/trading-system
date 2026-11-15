# pragma once // headers only

# include <cstring> // not being used yet
# include <iostream>
# include <cstdlib> // for EXIT_FAILURE

// Project is using C++20, so no need to define builtin macros

inline auto ASSERT(bool cond, const std::string &msg) noexcept {
	// catch only the exceptions
	if (!cond) [[unlikely]] {
		std::cerr << "ASSERT : " << msg << std::endl;

		exit(EXIT_FAILURE);
	}
}

inline auto FATAL(const std::string &msg) noexcept {
	std::cerr << "FATAL : " << msg << std::endl;

	// the program stops immediately,
	// as opposed to cout
	exit(EXIT_FAILURE);
}
