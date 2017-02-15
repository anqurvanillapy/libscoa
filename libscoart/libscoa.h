#ifndef __LIBSCOA_H
#define __LIBSCOA_H

#include <cstdint>

/// Runtime options.
enum {
    SCOA_THREADS_NUM    = 0,
    SCOA_THREADS_NOPIN  = 1 << 0,
    SCOA_AIO_PIN        = 1 << 1,
    SCOA_NOYIELD        = 1 << 2
}

#define SCOA_DEFAULT 0

typedef struct scoa_msg_t {
    // TODO
} scoa_msg_t;

namespace scoa {
    void init(uint32_t threads_num, int opt);
    void spawn(Actor& actor);
} // namespace scoa

#endif // !__LIBSCOA_H
