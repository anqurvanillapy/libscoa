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
    
    Actor(
        uint64_t id, 
        MessageQueue<scoa_msg_t>& inbox,
        MessageQueue<scoa_msg_t>& outbox );

    bool send(scoa_msg_t&);
    scoa_msg_t& receive(std::chrono::milliseconds);

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

/* Prototype of actor class for instantiation by scheduler */

class ActorPrototype {
public:
    ActorPrototype(Actor&);
private:
    uint64_t id;
    Msgq<scoa_msg_t> *inbox;
    Msgq<scoa_msg_t> *outbox;
};

#endif // !__LIBSCOA_ACTOR_H
