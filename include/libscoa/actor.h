#pragma once

#include "common.h"
#include "stackpool.h"
#include "msg.h"
#include "sched.h"

namespace scoa {

#define SCOA_MAX_ACTOR_NUM  64

class sched;

class matcher {
public:
	matcher& operator||(atom& a);
	std::function<SCOA_MATCHFN_TYPE>& getfn(unsigned aval);
private:
	static std::vector<std::function<SCOA_MATCHFN_TYPE>> patterns_;
};

class actor {
public:
	actor()             = delete;
	virtual ~actor()    = default;

	actor(int id, char* pool);

	friend class sched;

	inline int id() const { return id_; }
	virtual void be();
	void init();
private:
	void start_(void* msg);

	int id_;
	matcher matcher_;
	unsigned long hp_, sp_;
	std::jmp_buf env_;

	actor *prev_, *next_;
};

} /* namespace scoa */
