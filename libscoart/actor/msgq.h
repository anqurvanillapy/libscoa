#ifndef __LIBSCOA_MSGQ_H
#define __LIBSCOA_MSGQ_H

#include <boost/lockfree/queue.hpp>
#include "../libscoa.h"

/// Lock-free queue for implementing inbox/outbox
template <typename T>
class MessageQueue : public boost::lockfree::queue<T> {
public:
    MessageQueue();
};

#endif // !__LIBSCOA_MSGQ_H
