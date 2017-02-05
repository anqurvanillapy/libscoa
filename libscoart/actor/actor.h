#ifndef __LIBSCOA_ACTOR_H
#define __LIBSCOA_ACTOR_H

#include "../libscoa.h"
class Actor 
{
public:
    explicit Actor();
    
    Actor(
        uint64_t id, 
        MessageQueue<scoa_msg_t>& inbox,
        MessageQueue<scoa_msg_t>& outbox );

    bool send(scoa_msg_t &);
    scoa_msg_t& receive(std::chrono::milliseconds);

private:
    uint64_t scoa_id;
    // inbox and outbox manage by scheduler
    MessageQueue<scoa_msg_t> &inbox;
    MessageQueue<scoa_msg_t> &outbox;
}

#endif // !__LIBSCOA_ACTOR_H
