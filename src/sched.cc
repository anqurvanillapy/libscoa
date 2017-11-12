#include "libscoa/sched.h"

namespace scoa {

actor*          sched::current_actor{};
actor*          sched::actor_list   {};
int             sched::siz_         {};
std::jmp_buf    sched::main_env_    {};

void
sched::yield()
{
	if (::setjmp(main_env_)) {
		::longjmp(current_actor->env_, SCOA_ACTOR_YIELD);
	}
}

} /* namespace scoa */
