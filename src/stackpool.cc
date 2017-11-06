#include "libscoa/stackpool.h"

namespace scoa {

stackpool::stackpool()
	: nalloc_{SCOA_STACKPOOL_INITNUM}
{
	for (int i = 0; i < nalloc_; ++i) {
		auto sp = new char[SCOA_STACKSIZ];
		list_.push_back(sp);
	}
}

stackpool::~stackpool()
{
	int ndel = 0;
	for (auto sp : list_) {
		delete[] sp;
		++ndel;
	}
	assert(ndel == nalloc_ && "some buffers not released yet");
}

size_t
stackpool::size() const
{
	return list_.size();
}

char*
stackpool::acquire()
{
	if (list_.empty()) grow_();
	auto sp = list_.front();
	list_.pop_front();
	return sp;
}

void
stackpool::release(char* sp)
{
	list_.push_back(sp);
}

void
stackpool::grow_()
{
	assert(nalloc_ * 2 <= SCOA_MAX_ACTOR_NUM);
	for (int i = 0; i < nalloc_; ++i) {
		auto sp = new char[SCOA_STACKSIZ];
		list_.push_back(sp);
	}
	nalloc_ *= 2;
}

} /* namespace scoa */
