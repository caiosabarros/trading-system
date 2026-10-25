#include "thread_utils.h"

auto dummyFn(int a, int b, bool sleep) {
	std::cout << "dummyFn(" << a << "," << b << ")" << std::endl;
	for (int i=a; i < b; i++) {
		std::cout << i << "\n";
	}

	if (sleep) {
		std::cout << "sleeping now -_-" << std::endl;
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(5s);
	}

	std::cout << "dummy done" << std::endl;
}

int main(int, char **) {
	using namespace Common;

	auto t1 = createAndStartThread(-1, "dummy1", dummyFn, 12, 60, false);
	auto t2 = createAndStartThread(1, "dummy2", dummyFn, 13, 40, false);

	std::cout << "main waiting" << std::endl;
	t1->join();
	t2->join();
	std::cout << "main exiting" << std::endl;

	return 0;
}

