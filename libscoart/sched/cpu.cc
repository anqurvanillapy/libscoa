#include "cpu.h"
#include <thread>

uint32_t
scoa_cpu_count()
{
    return std::thread::hardware_concurrency();
}

bool
scoa_cpu_assign(uint32_t id, std::thread& thread, bool nopin, bool pinaio)
{
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);
    CPU_SET(id, &cpuset);
    int ret = pthread_setaffinity_np(thread.native_handle(), sizeof(cpu_set_t),
        &cpuset);

    if (ret != 0) return false;

    return true;
}
