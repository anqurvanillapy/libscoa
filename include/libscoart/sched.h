#pragma once

namespace scoa {

/// sched is the scheduler that handles tasks and messages from actors in the
/// queue.

class sched {
public:
    sched() { /* nop */ }
    ~sched() { /* nop */ }

    // No copy and move.
    sched(const sched&) = delete;
    sched& operator=(const sched&) = delete;
    sched(sched&&) = delete;
    sched& operator=(sched&&) = delete;
private:
};

} /* namespace scoa */
