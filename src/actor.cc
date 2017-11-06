#include "libscoa/actor.h"

namespace scoa {

thread_local sched tl_sched;

actor::actor(int id)
	: id_{id}
{
	/* nop */
}

actor::~actor()
{
	/* nop */
}

void
actor::start()
{
	be();
	tl_sched.yield();
}

} /* namespace scoa */
