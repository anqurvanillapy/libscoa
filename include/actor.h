#pragma once

#include "common.h"
#include "sched.h"

namespace scoa {

class sched;

class actor {
public:
	explicit actor(int id);
	virtual ~actor();

	virtual void be();
	void start();
private:
	int id_;
};

} /* namespace scoa */
