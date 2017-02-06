/**
 *  AIO
 *  ===
 *
 *  Asynchronous IO implemented by Linux's epoll and macOS/BSD's kqueue, for
 *  better portability.
 */

#ifndef __LIBSCOA_AIO_H
#define __LIBSCOA_AIO_H

#include "../libscoa.h"

#define MAX_EVENTS 64

// Wrapper type for platform-specific I/O notification mechanisms
typedef struct scoa_aio_facility scoa_aio_facility;

class AsyncIO {
public:
    scoa_aio_facility& get_aio_facility();
}

namespace scoa_aio {
    // TODO: Non-blocking stdio
    void putstd(int, std::string); // int - stdin, stdout, stderr
}

#endif // !__LIBSCOA_AIO_H
