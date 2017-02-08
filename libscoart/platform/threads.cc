// _GNU_SOURCE for CPU_SET
#ifdef __linux__
#define _GNU_SOURCE
#endif // __linux__

#include "../../common/platform.h"

#if defined(IS_LINUX) || defined(IS_FREEBSD)
#   include <sched.h>
#endif // IS_LINUX || IS_FREEBSD

#if defined(IS_FREEBSD)
#   include <pthread_np.h>  // FreeBSD's Non-POSIX type definitions
#   include <sys/cpuset.h>

typedef cpuset_t cpu_set_t;

#endif // IS_FREEBSD

bool
scoa_thread_create(scoa_thread_t& thread, thread_func start,
    u32int_t cpu, void* arg)
{
    (void)cpu;  // a thread is bound to a single CPU

#if defined(IS_LINUX) || defined(IS_FREEBSD)
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    if (cpu != (uint32_t)-1) {
        // TODO: set affinity
    }
#endif // IS_LINUX || IS_FREEBSD
}
