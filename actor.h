#pragma once

#include "ctx.h"

namespace scoa {

template <typename T>
class actor : public actor_base {
public:
	actor()     = default;
	~actor()    = default;

	actor(const actor<T>&)              = delete;
	actor& operator=(const actor<T>&)   = delete;
	actor(actor<T>&&)                   = delete;
	actor& operator=(actor<T>&&)        = delete;
private:
	virtual void
	be_() override
	{
		auto m = static_cast<T*>(this)->be();
		static_assert(std::is_invocable_v<decltype(m)>);

		while (!terminating_) {
		}
	}
};

} /* namespace scoa */
