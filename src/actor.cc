#include "libscoa/actor.h"

namespace scoa {

static thread_local sched tl_sched;

matcher&
matcher::operator||(atom& a)
{
	patterns_[a.val_] = a.f_;
	return *this;
}

std::function<SCOA_MATCHFN_TYPE>&
matcher::getfn(unsigned atom)
{
	return patterns_[atom];
}

actor::actor(int id, char* pool)
	: id_{id}
	, hp_{(unsigned long)pool}
	, sp_{hp_ + SCOA_STACKSIZ}
	, env_{}
	, prev_{}
	, next_{}
{
	assert(sp_);
	be();
}

void
actor::init()
{
	if (::setjmp(env_)) return;
#if defined(__i386__)
	__asm__ __volatile__(
		"movl %0, %%esp"
		:
		: "r"(tl_sched.current_actor->sp_)
		: "%esp"
	);
#elif defined(__x86_64__)
	__asm__ __volatile__(
		"movq %0, %%rsp"
		:
		: "r"(tl_sched.current_actor->sp_)
		: "%rsp"
	);
#endif
	void *msg = NULL;
	start_(msg);
}

void
actor::start_(void* msg)
{
	tl_sched.yield();
}

} /* namespace scoa */
