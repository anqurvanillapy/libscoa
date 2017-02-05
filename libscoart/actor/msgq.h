#ifndef __LIBSCOA_MSGQ_H
#define __LIBSCOA_MSGQ_H

#include <queue>
#include "../libscoa.h"
template <typename T>
class MessageQueue
{
public:
    explicit MessageQueue();

private:
    std::queue<T> q;
}

#endif // !__LIBSCOA_MSGQ_H