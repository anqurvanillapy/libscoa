#pragma once

#include "common.h"
#include "sched.h"

namespace scoa {

typedef int_fast32_t scoa_msg_int32_t;
typedef int_fast64_t scoa_msg_int64_t;

typedef struct {
} scoa_msg_t;

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
