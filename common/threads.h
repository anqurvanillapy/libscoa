/**
 *  Threads
 *  =======
 *
 *  Platform-specific multithreading support
 */

#ifndef __LIBSCOA_THREADS_H
#define __LIBSCOA_THREADS_H

#ifdef IS_POSIX_BASED
#   include <pthread.h>
#   define scoa_thread_t pthread_t
#   define DECLARE_THREAD_FUNC(FUNC_NAME) void* FUNC_NAME (void* arg)

typedef void* (*thread_func) (void* arg);

#endif // IS_POSIX_BASED

bool scoa_thread_create(scoa_thread_t& thread, thread_func start,
    u32int_t cpu, void* arg);
bool scoa_thread_join(scoa_thread_t& thread);
bool scoa_thread_detach(scoa_thread_t& thread);

#endif // !__LIBSCOA_THREADS_H
