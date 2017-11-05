#include <iostream>
#include <thread>
#include "lfq.h"

#define LEN 1000

int
main()
{
    scoa::lockfreeq<int> q;
    std::thread t1([&] { for (int i = 0; i < LEN; ++i) q.push_back(i); });
    std::thread t2([&] { for (int i = 0; i < LEN; ++i) q.push_back(i); });
    std::thread t3([&] { for (int i = 0; i < LEN; ++i) q.push_back(i); });
    t1.join();
    t2.join();
    t3.join();
    std::cout << q.size() << std::endl;
    for (int i = 0; i < LEN * 3; ++i) std::cout << q.pop_front() << "\n";
    return 0;
}
