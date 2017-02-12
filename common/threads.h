#ifndef __LIBSCOA_THREADS_H
#define __LIBSCOA_THREADS_H

#include <thread>

#ifdef IS_POSIX_BASED
typedef void* (*thread_func) (void* arg);
#endif // IS_POSIX_BASED

#if defined(IS_LINUX)
#   include <pthread.h>
#elif defined(IS_FREEBSD)
#   include <pthread_np.h>  // FreeBSD's Non-POSIX type definitions
#   include <sys/cpuset.h>

typedef cpuset_t cpu_set_t;

#endif // IS_LINUX

#endif // !__LIBSCOA_THREADS_H
