/**
 *  AIO
 *  ===
 *
 *  Asynchronous I/O implemented by Linux's epoll and macOS/BSD's kqueue, for
 *  better portability.
 */

#ifndef __LIBSCOA_AIO_H
#define __LIBSCOA_AIO_H

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
}

class AsyncIO {
public:
    // Initialize the notification mechanism.
    AsyncIO();
    ~AsyncIO();

    // Make it callable by the thread.
    void operator() ();

    // Terminate the mechanism.
    void final();
private:
    uint32_t cpu;
    std::thread::id tid;

#if defined(AIO_USE_EPOLL)
    int epfd;
    int evfd;
    struct epoll_event events[MAX_EVENTS];
    std::atomic_bool terminated;    
#elif defined(AIO_USE_KQUEUE)
#endif
}

void scoa_aio_start();

bool scoa_aio_stop();

namespace scoa {
    // TODO: Non-blocking stdio
    void fputs(int fd, std::string str); // int - stdin, stdout, stderr
} // namespace scoa

#endif // !__LIBSCOA_AIO_H
