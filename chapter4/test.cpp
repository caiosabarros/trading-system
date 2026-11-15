# include "macros.h"
# include <iostream>
# include "mem_pool.h"

int main() {
	int x = 5;

	if (x == 5) [[likely]] {
		std::cout << "RIGHT" << std::endl;
	}

	if (x == 10) [[unlikely]] {
		std::cout << "SURPRISE!" << std::endl;
	}

	ASSERT(x == 5, "!wrong");

	// ASSERT(x == 7, "x is different!");

	FATAL("International Error");

	return 0;
}


