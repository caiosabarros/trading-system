// print all the memory pool pointers :)
#include "mem_pool.h"

struct MyStruct {
	int d_[3];
};

int main(int, char **) {

	using namespace Common;

	MemPool<double> prim_pool(50); // this is an empty MemPool with 50 empty spaces to receive allocation
	MemPool<MyStruct> struct_pool(50); // empty MemPool with 50 empty spaces
	std::vector<double*> raw_ptrs;

	for(auto i=0; i < 50; i++) {
		auto p_ret = prim_pool.allocate(i); // allocate the number i in one of those 50 empty spaces
		// in i = 49, it will allocate 49,50,51!
		auto s_ret = struct_pool.allocate(MyStruct{i, i+1, i+2}); // allocate the three consecutive numbers together

		raw_ptrs.push_back(p_ret);

		std::cout << "prim elem:" << *p_ret << " allocated at:" << p_ret << std::endl;
		std::cout << "struct elem:" << s_ret->d_[0] << "," << s_ret->d_[1] << "," << s_ret->d_[2] << " allocated at:" << s_ret << std::endl;

		if(i % 5 == 0) {
			std::cout << "deallocating prim elem:" << *p_ret << " from:" << p_ret << std::endl;
			std::cout << "deallocating struct elem:" << s_ret->d_[0] << "," << s_ret->d_[1] << "," << s_ret->d_[2] << " from:" << s_ret << std::endl;

			prim_pool.deallocate(p_ret);
			struct_pool.deallocate(s_ret);
		}

	}

	// check the layout
	std::cout << "MEMORY LAYOUT" << std::endl;
	auto i = raw_ptrs.rbegin(); // start at reverse begin
	do {
		std::cout << *i << std::endl; // i is a ptr, that's why the dereference
		i++; // increase because the rbegin, rend works this incrementally
	} while (i != raw_ptrs.rend());

	// hit the assert - allocate to an already occupied element by running another loop on all elements
	// for (auto i = 0; i < 50; i++) {
	// 	std::cout << "Break at loop i: " << i << std::endl; -> 9 is the last shown
	//	prim_pool.allocate(i); // ASSERT : Memory Pool out of space' whenever the mem pool is full
	// }


	// hit the assert - obj from different memory pool being deallocated from another mem pool
	MemPool<double> fake_prim_pool(2);
	auto f_ret = fake_prim_pool.allocate(1234.);
	prim_pool.deallocate(f_ret); // ASSERT : Element being deallocated does not belong to this Memory pool.

	return 0;
}
