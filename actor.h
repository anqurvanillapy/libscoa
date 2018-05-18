#pragma once

#include <type_traits>
#include <csetjmp>

#include "ctx.h"

namespace scoa {

class sched;

class actor_base {
public:
	virtual void send()     = 0;

	friend class sched;
	template <typename T> friend class actor;
protected:
	virtual void be_()      = 0;
	virtual void recv_()    = 0;

	size_t sp_;
	std::jmp_buf env_;
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
	}

	bool terminating_{};

};

} /* namespace scoa */
