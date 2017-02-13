/**
 *  Asnyc I/O
 *  =========
 *
 *  Asynchronous I/O implemented by Linux's epoll and macOS/BSD's kqueue, for
 *  better portability.
 */

#ifndef __LIBSCOA_ASYNCIO_H
#define __LIBSCOA_ASYNCIO_H

#include "../libscoa.h"
#include "../../common/platform.h"
#include <thread>
#include <atomic>

#if defined(IS_LINUX)
#   define AIO_USE_EPOLL
#   include <sys/epoll.h>
#   include <sys/eventfd.h>
#elif defined(IS_MACOS) || defined(IS_FREEBSD)
#   define AIO_USE_KQUEUE
#else
#   error PLATFORM NOT SUPPORTED!
#endif

#define MAX_EVENTS 64

/// Asynchronous I/O events.
enum {
    AIO_READ        = 0,
    AIO_WRITE       = 1 << 0,
    AIO_DESTROYED   = (uint32_t)-1
};

class AsyncIOFacility {
public:
    explicit AsyncIOFacility();
    ~AsyncIOFacility();

    // Function for aio_thread to run.
    void thread_func();
private:
    std::thread* aio_thread;

#if defined(AIO_USE_EPOLL)
    int epfd;
    int evfd;
    struct epoll_event events[MAX_EVENTS];
    std::atomic_bool terminated;    
#elif defined(AIO_USE_KQUEUE)
#endif
};

void scoa_aio_start(uint32_t cpu);

bool scoa_aio_stop();

#endif // !__LIBSCOA_AIO_H
