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

#if defined(IS_LINUX)
#   define AIO_USE_EPOLL
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

class AIOFacility {
public:
    AIOFacility();
    bool destroy();
private:
#if defined(AIO_USE_EPOLL)
    int epfd;
    struct epoll_event events[MAX_EVENTS];
#elif defined(AIO_USE_KQUEUE)
#endif
}

class AsyncIO {
public:
    // Constructed after a scheduler is initialized.
    AsyncIO();

    // Start an AsyncIO instance after a scheduler run its thread.
    void start();

    // Stop the event mechanism.
    void stop();
private:
    uint32_t cpu;
    scoa_thread_id_t tid;
    AIOFacility* facility;
}

namespace scoa {
    // TODO: Non-blocking stdio
    void fputs(int fd, std::string str); // int - stdin, stdout, stderr
} // namespace scoa

#endif // !__LIBSCOA_AIO_H
