#pragma once

#include "common.h"

namespace scoa {

/// lockfreeq is the prototype of message queues and in-/out-boxes that can
/// atomically enqueue/dequeue.

template <typename T>
class lockfreeq {
public:
    lockfreeq() { /* nop */ }
    virtual ~lockfreeq() { /* nop */ }

    // No copy and move.
    lockfreeq(const lockfreeq&) = delete;
    lockfreeq& operator=(const lockfreeq&) = delete;
    lockfreeq(lockfreeq&&) = delete;
    lockfreeq& operator=(lockfreeq&&) = delete;

    auto front() const { return head; }
    auto back() const { return tail; }

    auto
    pop_back()
    {
    }

    void
    push_back(T elem)
    {
    }

    auto
    pop_front()
    {
    }

    void
    push_front(T elem)
    {
    }
private:
    struct lfq_node {
        T t;
        shared_ptr<lfq_node> next;
    }

    std::atomic_size_t len{0};
    std::shared_ptr<lfq_node> head;
    std::shared_ptr<lfq_node> tail;
};

} /* namespace scoa */
