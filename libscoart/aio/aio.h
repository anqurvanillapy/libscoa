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

// Wrapper type for platform-specific I/O notification mechanisms
typedef struct scoa_aio_facility scoa_aio_facility;

class AsyncIO {
public:
    scoa_aio_facility& get_aio_facility();
}

namespace scoa {
    // TODO: Non-blocking stdio
    void fputs(int, std::string); // int - stdin, stdout, stderr
} // namespace scoa

#endif // !__LIBSCOA_AIO_H
