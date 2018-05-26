#pragma once

#include <type_traits>
#include <atomic>
#include <memory>
#include <cassert>

namespace scoa {

#define UNLIKELY(cond) __builtin_expect(static_cast<bool>((cond)), 0)

template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
using owner = T;

template <typename... Ts>
struct match : Ts... {
	using Ts::operator()...;
};

template <typename... Ts>
match(Ts...) -> match<Ts...>;

inline uint64_t
rdtsc()
{
	uint32_t low, high;
	__asm__ __volatile__ ("rdtsc" : "=a"(low), "=d"(high));
	return (uint64_t)high << 32 | low;
}

inline void
thread_pause()
{
	__asm__ __volatile__ ("pause" ::: "memory");
}

template <typename T>
class spmcq {
public:
	spmcq()
	{
		auto n = new (std::nothrow) _node_t();
		assert(n);
		n->data.store(nullptr, std::memory_order_relaxed);
		n->next.store(nullptr, std::memory_order_relaxed);
		h_.store(n, std::memory_order_relaxed);

		_refcnt_t<_node_t*> t;
		t.obj = n;
		t.cnt = 0;
		t_.store(t, std::memory_order_relaxed);
	}

	~spmcq()
	{
		h_.store(nullptr, std::memory_order_relaxed);
		auto t = t_.load(std::memory_order_relaxed);
		delete t.obj;
		t.obj = nullptr;
		t_.sotre(t, std::memory_order_relaxed);
	}

	spmcq(const spmcq<T>&)              = delete;
	spmcq& operator=(const spmcq<T>&)   = delete;
	spmcq(spmcq<T>&&)                   = delete;
	spmcq& operator=(spmcq<T>&&)        = delete;

	void
	push(owner<T> data)
	{
		auto n = new (std::nothrow) _node_t;
		assert(n);
		n->data.store(nullptr, std::memory_order_relaxed);
		n->next.store(nullptr, std::memory_order_relaxed);
		auto prev =
			std::atomic_exchange_explicit(h_, n, std::memory_order_relaxed);
		h_.store(n, std::memory_order_release);
		data = nullptr;
	}

	void
	push_single(owner<T> data)
	{
		auto n = new (std::nothrow) _node_t;
		assert(n);
		n->data.store(data, std::memory_order_relaxed);
		n->next.store(nullptr, std::memory_order_relaxed);
		auto prev = h_.load(std::memory_order_relaxed);
		h_.store(n, std::memory_order_relaxed);
		prev->next.store(n, std::memory_order_relaxed);
		data = nullptr;
	}

	owner<T>
	pop()
	{
		_refcnt_t<_node_t*> cmp = t_.load(std::memory_order_relaxed);
		_refcnt_t<_node_t*> xchg;
		_node_t* t, next;

		do {
			t = cmp.obj;
			next = t->next.load(std::memory_order_relaxed);
			if (UNLIKELY(next == nullptr)) {
				return nullptr;
			}
			xchg.obj = next;
			xchg.cnt = cmp.cnt + 1;
		} while (
			!std::atomic_compare_exchange_weak_explicit(
				t_, &t, next,
				std::memory_order_relaxed,
				std::memory_order_relaxed
			)
		);

		std::atomic_thread_fence(std::memory_order_acq_rel);
		auto data = next->data.load(std::memory_order_relaxed);
		next->data.store(nullptr, std::memory_order_relaxed);

		while (t->data.load(std::memory_order_relaxed) != nullptr) {
			thread_pause();
		}

		std::atomic_thread_fence(std::memory_order_acquire);
		delete t;
		t = nullptr;

		return data;
	}
private:
	template <typename U>
	struct _refcnt_t {
		U obj;
		std::size_t cnt;
	};

	struct _node_t {
		std::atomic<T> data;
		std::atomic<_node_t*> next;
	};

	alignas(64) std::atomic<_node_t*> h_;
	alignas(64) _refcnt_t<_node_t*> t_;
};

template <typename T, std::size_t Siz>
class mpmcq {
public:
};

} /* namespace scoa */
