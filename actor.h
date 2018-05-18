#pragma once

#include <type_traits>
#include <csetjmp>

#include "ctx.h"

namespace scoa {

class sched;

class actor_base {
public:
	actor_base()
		: hp_{new char[CO_CALLSTACK_SIZ]}
		, sp_{hp_ + CO_CALLSTACK_SIZ}
	{
	}

	friend class sched;
	template <typename T> friend class actor;

	void send();
protected:
	virtual void be_()      = 0;
	void recv_();

	void
	init_env_()
	{
		if (::setjmp(env_)) start_();
	}

	static void
	start_()
	{
#if defined(__i386__)
		__asm__ __volatile__ (
			"movl %0， %%esp"
			:
			: "r"(sched::current_actor_->sp_)
			: "%esp"
		);
#elif defined(__x86_64__)
		__asm__ __volatile__(
			"movq %0, %%rsp"
			:
			: "r"(sched::current_actor_->sp_)
			: "%rsp"
		);
#endif
		sched::current_actor_->be_();
		::longjmp(sched::main_env_, static_cast<int>(_co_rc_t::END));
	}

	char* hp_;
	char* sp_;
	std::jmp_buf env_;
	bool terminating_{};
};

template <typename T>
class actor : public actor_base {
public:
	actor()     = default;
	~actor()    = default;

	actor(const actor<T>&)              = delete;
	actor& operator=(const actor<T>&)   = delete;
	actor(actor<T>&&)                   = delete;
	actor& operator=(actor<T>&&)        = delete;
private:
	virtual void
	be_() override
	{
		auto m = static_cast<T*>(this)->be();
		static_assert(std::is_invocable_v<decltype(m)>);

		while (!terminating_) {
		}
	}
};

} /* namespace scoa */
