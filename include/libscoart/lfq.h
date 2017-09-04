#pragma once

#include "common.h"

namespace scoa {

/// lockfreeq is the prototype of message queues and in-/out-boxes that can
/// atomically enqueue/dequeue.

class lockfreeq {
public:
    lockfreeq() { /* nop */ }
    virtual ~lockfreeq() { /* nop */ }

    // No copy and move.
    lockfreeq(const lockfreeq&) = delete;
    lockfreeq& operator=(const lockfreeq&) = delete;
    lockfreeq(lockfreeq&&) = delete;
    lockfreeq& operator=(lockfreeq&&) = delete;
private:
};

} /* namespace scoa */
