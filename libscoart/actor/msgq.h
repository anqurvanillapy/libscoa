#ifndef __LIBSCOA_MSGQ_H
#define __LIBSCOA_MSGQ_H

#include <boost/lockfree/queue.hpp>
#include "../libscoa.h"

template <typename T>
class MessageQueue : public boost::lockfree::queue<T> {
public:
    MessageQueue();
}

#endif // !__LIBSCOA_MSGQ_H
