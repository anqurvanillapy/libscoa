#pragma once

#include "common.h"
#include "lfq.h"

namespace scoa {

/// messageq is the message queue manipulated by a scheduler.

class messageq : public lockfreeq {
public:
    messageq() { /* nop */ }
    ~messageq() { /* nop */ }

    // No copy and move.
    messageq(const messageq&) = delete;
    messageq& operator=(const messageq&) = delete;
    messageq(messageq&&) = delete;
    messageq& operator=(messageq&&) = delete;
private:
};

} /* namespace scoa */
