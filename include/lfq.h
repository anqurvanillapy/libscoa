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
		lfq_node() = default;
		explicit lfq_node(const T& data) : data(data) { /* nop */ }
	};
public:
	lockfreeq() : head_(std::make_shared<lfq_node>()), tail_(head_),
		dummy_node_(std::make_shared<lfq_node>()) { /* nop */ }
	virtual ~lockfreeq() = default;

	lockfreeq(const lockfreeq&) = delete;
	lockfreeq& operator=(const lockfreeq&) = delete;
	lockfreeq(lockfreeq&&) = delete;
	lockfreeq& operator=(lockfreeq&&) = delete;

	inline size_t size() const { return siz_.load(); }

	void
	push_back(const T& elem)
	{
		auto new_node = std::make_shared<lfq_node>(elem);
		std::shared_ptr<lfq_node> t;
		while (true) {
			t = std::atomic_load_explicit(&tail_, std::memory_order_relaxed);
			auto next = t->next;
			if (t != tail_) continue;
			if (next != nullptr) {
				if (std::atomic_compare_exchange_weak_explicit(&tail_, &t, next,
						std::memory_order_release,
						std::memory_order_relaxed)) continue;
			}
			if (t != tail_) continue;
			if (std::atomic_compare_exchange_weak_explicit(
						&t->next,
						&dummy_node_,
						new_node,
						std::memory_order_release,
						std::memory_order_relaxed)) break;
		}
		std::atomic_compare_exchange_weak_explicit(&tail_, &t, new_node,
				std::memory_order_release,
				std::memory_order_relaxed);
		siz_.fetch_add(1, std::memory_order_relaxed);
	}

	T
	pop_front()
	{
		T data;
		while (true) {
			auto h = std::atomic_load_explicit(&head_,
					std::memory_order_relaxed);
			auto t = std::atomic_load_explicit(&tail_,
					std::memory_order_relaxed);
			auto next = h->next;
			if (h != head_) continue;
			if (next == nullptr) throw std::runtime_error("empty queue");
			if (h == t) {
				if (std::atomic_compare_exchange_weak_explicit(&tail_, &t, next,
						std::memory_order_release,
						std::memory_order_relaxed)) continue;
			}
			if (h != head_) continue;
			data = next->data;
			if (std::atomic_compare_exchange_weak_explicit(&head_, &h, next,
						std::memory_order_release,
						std::memory_order_relaxed)) break;
		}
		siz_.fetch_sub(1, std::memory_order_relaxed);
		return data;
	}
private:
	std::atomic_size_t siz_{0};
	std::shared_ptr<lfq_node> head_, tail_, dummy_node_;
};

} /* namespace scoa */
