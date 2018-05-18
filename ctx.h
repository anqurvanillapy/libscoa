#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <cstring>
#include <csetjmp>

#define CO_CALLSTACK_SIZ    (4 * 1024)
#define MAX_ACTOR_NUM       32

namespace scoa {

class actor_base;
template <typename T> class actor;

namespace {

enum class _co_rc_t {
	INIT,
	END,
	NEXT = 1,
	YIELD
};

} /* namespace */

class sched {
public:
	sched()     = default;
	~sched()    = default;

	sched(const sched&)             = delete;
	sched& operator=(const sched&)  = delete;
	sched(sched&&)                  = delete;
	sched& operator=(sched&&)       = delete;

	template <typename T> friend class actor;

	void
	steal()
	{
		nactor_.fetch_add(1, std::memory_order_relaxed);
	}
private:
	thread_local static actor_base* current_actor_;
	std::atomic_uint nactor_;
};

class ctx {
public:
	ctx()
		: ncores_{std::thread::hardware_concurrency()}
		, scheds_{new sched*[ncores_]}
	{
		ts_.reserve(ncores_);
		for (unsigned i = 0; i < ncores_; ++i) scheds_[i] = new sched;
	}

	~ctx()
	{
		for (unsigned i = 0; i < ncores_; ++i) delete scheds_[i];
		delete[] scheds_;
		scheds_ = nullptr;
	}

	ctx(const ctx&)             = delete;
	ctx& operator=(const ctx&)  = delete;
	ctx(ctx&&)                  = delete;
	ctx& operator=(ctx&&)       = delete;

	void
	spawn()
	{
	}

	void
	spawn_dispatch()
	{
	}

	void
	start()
	{
		for (auto&& t : ts_) {
			t = std::thread([] {});
		}
		for (auto&& t : ts_) t.join();
	}
private:
	unsigned ncores_{std::thread::hardware_concurrency()};
	sched** scheds_;
	std::vector<std::thread> ts_;
};

} /* namespace scoa */
