#include <thread>
#include <iostream>

int main() {
	std::cout << "Threads on my computer: " << std::thread::hardware_concurrency() << "\n";
	return 0;
}

