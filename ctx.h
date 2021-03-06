#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <cstring>
#include <csetjmp>

#define MAX_ACTOR_NUM       32
#define CO_CALLSTACK_SIZ    (4 * 1024)

namespace scoa {

class actor_base;

namespace {

enum class _co_rc_t : int {
	INIT,
	END,
	NEXT = 1,
	YIELD
};

} /* namespace */

/*
 *  ============================================================================
 *  Scheduler
 *  ============================================================================
 */

class sched {
public:
	sched()     = default;
	~sched()    = default;

	sched(const sched&)             = delete;
	sched& operator=(const sched&)  = delete;
	sched(sched&&)                  = delete;
	sched& operator=(sched&&)       = delete;

	friend class actor_base;

	static void steal();
	static void yield();

	void
	add(actor_base* a)
	{
		actor_list_.emplace_back(a);
		nactor_.fetch_add(1, std::memory_order_relaxed);
	}
private:
	thread_local static actor_base*             current_actor_;
	thread_local static std::list<actor_base*>  actor_list_;

	thread_local static std::atomic_uint        nactor_;
	thread_local static std::jmp_buf            main_env_;
};

thread_local actor_base*            sched::current_actor_{};
thread_local std::list<actor_base*> sched::actor_list_{};
thread_local std::atomic_uint       nactor_{};
thread_local std::jmp_buf           main_env_{};

/*
 *  ============================================================================
 *  Actor (abstract class)
 *  ============================================================================
 */

class actor_base {
public:
	actor_base()
		: hp_{new char[CO_CALLSTACK_SIZ]}
		, sp_{hp_ + CO_CALLSTACK_SIZ}
	{
		/* nop */
	}

	~actor_base()
	{
		delete[] hp_;
	}

	friend class sched;
	template <typename T> friend class actor;

	std::string
	id() const
	{
		return id_;
	}

	void send();
protected:
	virtual void be_() = 0;

	void recv_();

	void
	init_env_()
	{
		if (::setjmp(env_)) {
			start_();
		}
	}

	static void
	start_()
	{
		auto sp = reinterpret_cast<size_t>(sched::current_actor_->sp_);

		__asm__ __volatile__(
			"movq %0, %%rsp"
			:
			: "r"(sp)
			: "%rsp"
		);

		sched::current_actor_->be_();
		::longjmp(sched::main_env_, static_cast<int>(_co_rc_t::END));
	}

	std::string id_;

	char* hp_;
	char* sp_;
	std::jmp_buf env_;
	bool terminating_{};
};

void
sched::steal()
{
	nactor_.fetch_add(1, std::memory_order_relaxed);
}

void
sched::yield()
{
	if (!::setjmp(current_actor_->env_)) {
		::longjmp(main_env_, static_cast<int>(_co_rc_t::YIELD));
	}
}

/**
 *  ============================================================================
 *  Context
 *  ============================================================================
 */

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
	unsigned ncores_;
	sched** scheds_;
	std::vector<std::thread> ts_;
};

} /* namespace scoa */
