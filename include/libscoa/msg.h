#pragma once

#include "common.h"
#include "actor.h"

#define Err 0u
#define Ok  1u

namespace scoa {

class atom {
public:
	atom()  = delete;
	~atom() = default;

	explicit atom(unsigned val);

	atom(const atom&)               = delete;
	atom& operator=(const atom&)    = delete;
	atom(atom&&)                    = delete;
	atom& operator=(atom&&)         = delete;

	friend class matcher;

	void operator>>(const std::function<void(void*)>& f);
private:
	unsigned val_;
	std::function<void(void*)> f_;
};

using A = atom;

} /* namespace scoa */
