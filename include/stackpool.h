#pragma once

#include "common.h"

namespace scoa {

class stackpool {
public:
	stackpool();
	~stackpool();

	stackpool(const stackpool&)             = delete;
	stackpool& operator=(const stackpool&)  = delete;
	stackpool(stackpool&&)                  = delete;
	stackpool& operator=(stackpool&&)       = delete;

	size_t size() const;
	char* acquire();
	void release(char* sp);
private:
	void grow_();

	int nalloc_;
	std::list<char*> list_;
};

} /* namespace scoa */
