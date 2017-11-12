#include "libscoa/msg.h"

namespace scoa {

atom::atom(unsigned val)
	: val_{val}
{
	/* nop */
}
void
atom::operator>>(const std::function<SCOA_MATCHFN_TYPE>& f)
{
	f_ = f;
}

} /* namespace scoa */
