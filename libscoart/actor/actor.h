/**
 *  Actor
 *  =====
 *
 *  Interface for user-defined behaviours and implementations of actors, used by
 *  scheduler to instantiate the ActorPrototype.
 */

#ifndef __LIBSCOA_ACTOR_H
#define __LIBSCOA_ACTOR_H

#include "../libscoa.h"
#include "../sched/sched.h"
#include "msgq.h"

class Actor 
{
public:
    Actor();
    
    explicit Actor(uint64_t id, MessageQueue<scoa_msg_t>& inbox,
        MessageQueue<scoa_msg_t>& outbox );

    bool        send(scoa_msg_t& msg);
    scoa_msg_t& recv(std::chrono::milliseconds timeout);
    void        be(void *arg);

private:
    uint64_t scoa_id;
    // inbox and outbox manage by scheduler
    MessageQueue<scoa_msg_t>& inbox;
    MessageQueue<scoa_msg_t>& outbox;
    // in which scheduler    
    Scheduler& scheduler;
    // waiting_for asyncio event id
    uint64_t   waiting_for;
}

#endif // !__LIBSCOA_ACTOR_H
