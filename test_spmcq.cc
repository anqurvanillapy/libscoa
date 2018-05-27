#include <iostream>
#include <thread>
#include "util.h"

#define N 8

#ifdef SCOA_TEST_SINGLE
int
main()
#else
void
test_spmcq()
#endif /* SCOA_TEST_SINGLE */
{
	std::thread p, c0, c1;
	scoa::spmcq<int*> q;

	p = std::thread([&] {
		for (size_t i = 0; i < N; ++i) {
			// q.push_single(reinterpret_cast<int*>(i * sizeof(int)));
			q.push(reinterpret_cast<int*>(i * sizeof(int)));
		}
	});
	p.join();

	c0 = std::thread([&] {
		for (size_t i = 0; i < N / 2; ++i) {
			std::cout << q.pop() << std::endl;
		}
	});
	c1 = std::thread([&] {
		for (size_t i = 0; i < N / 2; ++i) {
			std::cout << q.pop() << std::endl;
		}
	});
	c0.join();
	c1.join();
}
