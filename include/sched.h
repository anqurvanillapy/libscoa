#pragma once

#include "common.h"

namespace scoa {

class sched {
public:
	sched()     = default;
	~sched()    = default;

	sched(const sched&)             = delete;
	sched& operator=(const sched&)  = delete;
	sched(sched&&)                  = delete;
	sched& operator=(sched&&)       = delete;
private:
};

} /* namespace scoa */
