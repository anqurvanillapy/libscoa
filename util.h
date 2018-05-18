#pragma once

#include <type_traits>
#include <atomic>

namespace scoa {

template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
using owner = T;

template <typename T>
class ts_list {
public:
	ts_list() = default;

	~ts_list()
	{
		_node_t* h, tmp;

		if ( (h = h_.load(std::memory_order_relaxed))) {
			while (true) {
				tmp = h;
				h = h->next;
				delete tmp;
				if (h->next == nullptr) break;
			}
		}
	}

	ts_list(const ts_list<T>&)              = delete;
	ts_list& operator=(const ts_list<T>&)   = delete;
	ts_list(ts_list<T>&&)                   = delete;
	ts_list& operator=(ts_list<T>&&)        = delete;

	auto
	size() const
	{
		return siz_.load(std::memory_order_relaxed);
	}

	void
	push_front(owner<T> data)
	{
		_node_t* const n = new _node_t(data);
		n->next = h_.load(std::memory_order_relaxed);
		while (!h_.compare_exchange_weak(n->next, n));
		data = nullptr;
		siz_.fetch_add(1, std::memory_order_relaxed);
	}

	owner<T>
	pop_front()
	{
		_node_t* h = h_.load(std::memory_order_relaxed);
		while (!h_.compare_exchange_weak(h, h->next));
		siz_.fetch_sub(1, std::memory_order_relaxed);
		return h->data;
	}
private:
	struct _node_t {
		T data;
		_node_t* next;

		_node_t(T d)
			: data(d)
		{
			/* nop */
		}
	};

	std::atomic<_node_t*> h_;
	std::atomic_uint siz_;
};

template <typename T, std::size_t Siz>
class ts_ringbuf {
public:
};

template <typename... Ts>
struct match : Ts... {
	using Ts::operator()...;
};

template <typename... Ts>
match(Ts...) -> match<Ts...>;

} /* namespace scoa */
