#pragma once

#include "common.h"
#include "sched.h"

namespace scoa {

/// aio_sched is a special scheduler that handle the asynchronous I/O.

class aio_sched : public sched {
public:
    aio_sched() { /* nop */ }
    ~aio_sched() { /* nop */ }

    // No copy and move.
    aio_sched(const aio_sched&) = delete;
    aio_sched& operator=(const aio_sched&) = delete;
    aio_sched(aio_sched&&) = delete;
    aio_sched& operator=(aio_sched&&) = delete;
private:
};

} /* namespace scoa */
