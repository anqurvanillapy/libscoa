#pragma once

#include "common.h"

namespace scoa {

/// lockfreeq is the prototype of message queues and in-/out-boxes that can
/// atomically enqueue/dequeue.

template <typename T>
class lockfreeq {
protected:
    struct lfq_node {
        T data;
        std::shared_ptr<lfq_node> next;
        lfq_node() { /* nop */ }
        explicit lfq_node(const T& data) : data(data) { /* nop */ }
    };
public:
    lockfreeq()
        : head_(std::make_shared<lfq_node>()),
        tail_(head_),
        dummy_nullsptr_(std::make_shared<lfq_node>())
    { /* nop */ }
    virtual ~lockfreeq() { /* nop */ }

    // No copy and move.
    lockfreeq(const lockfreeq&) = delete;
    lockfreeq& operator=(const lockfreeq&) = delete;
    lockfreeq(lockfreeq&&) = delete;
    lockfreeq& operator=(lockfreeq&&) = delete;

    size_t
    size() const
    {
        return siz_.load(std::memory_order_relaxed);
    }

    void
    push_back(const T& elem)
    {
        std::shared_ptr<lfq_node> t;
        auto new_node = std::make_shared<lfq_node>(elem);

        while (true) {
            t = std::atomic_load_explicit(&tail_, std::memory_order_relaxed);
            hp_[0].store(t.get(), std::memory_order_relaxed);
            if (t.get() != tail_.get()) continue;
            if (t->next != nullptr) {
                std::atomic_compare_exchange_weak_explicit(
                        &tail_,
                        &t,
                        t->next,
                        std::memory_order_release,
                        std::memory_order_relaxed);
                continue;
            }
            if (std::atomic_compare_exchange_weak_explicit(
                        &t->next,
                        &dummy_nullsptr_,
                        new_node,
                        std::memory_order_release,
                        std::memory_order_relaxed)) break;
        }
        std::atomic_compare_exchange_weak_explicit(
                &tail_,
                &t,
                new_node,
                std::memory_order_release,
                std::memory_order_relaxed);
        siz_.fetch_add(1, std::memory_order_relaxed);
    }

    T
    pop_front()
    {
        T ret;
        std::shared_ptr<lfq_node> h, t;

        while (true) {
            h = std::atomic_load_explicit(&head_, std::memory_order_relaxed);
            hp_[0].store(h.get(), std::memory_order_relaxed);
            if (h.get() != head_.get()) continue;
            auto t = std::atomic_load_explicit(&tail_,
                    std::memory_order_relaxed);
            auto next = h->next;
            hp_[1].store(next.get(), std::memory_order_relaxed);
            if (h.get() != head_.get()) continue;
            if (next == nullptr) throw std::runtime_error("empty queue");
            if (h == std::atomic_load_explicit(&tail_,
                        std::memory_order_relaxed)) {
                std::atomic_compare_exchange_weak_explicit(
                        &tail_,
                        &t,
                        next,
                        std::memory_order_release,
                        std::memory_order_relaxed);
                continue;
            }
            ret = next->data;
            if (std::atomic_compare_exchange_weak_explicit(
                        &head_,
                        &h,
                        next,
                        std::memory_order_release,
                        std::memory_order_relaxed)) break;
        }

        siz_.fetch_sub(1, std::memory_order_relaxed);
        return ret;
    }
private:
    std::atomic_size_t siz_{0};
    std::shared_ptr<lfq_node> head_, tail_, dummy_nullsptr_;

    // Hazard pointers.
    std::atomic<lfq_node*> hp_[2]{};
};

} /* namespace scoa */
