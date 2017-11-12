#pragma once

#include "common.h"
#include "actor.h"

namespace scoa {

enum {
	SCOA_ACTOR_INIT,
	SCOA_ACTOR_END,
	SCOA_ACTOR_YIELD
};

class sched {
public:
	sched()     = default;
	~sched()    = default;

	sched(const sched&)             = delete;
	sched& operator=(const sched&)  = delete;
	sched(sched&&)                  = delete;
	sched& operator=(sched&&)       = delete;

	inline int size() const { return siz_; }
	void run();
	void yield();

	static actor* current_actor;
	static actor* actor_list;
private:
	static int siz_;
	static std::jmp_buf main_env_;
};

} /* namespace scoa */
