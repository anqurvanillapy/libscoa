#include "../include/actor.h"

namespace scoa {

thread_local sched tlsched;

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
	tlsched.yield();
}

} /* namespace scoa */
