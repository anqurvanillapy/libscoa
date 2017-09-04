#pragma once

#include "common.h"
#include "lfq.h"

namespace scoa {

/// taskq is the queue for pending tasks from actors.

class taskq : public lockfreeq {
public:
    taskq() { /* nop */ }
    ~taskq() { /* nop */ }

    // No copy and move.
    taskq(const taskq&) = delete;
    taskq& operator=(const taskq&) = delete;
    taskq(taskq&&) = delete;
    taskq& operator=(taskq&&) = delete;
private:
};

} /* namespace scoa */
