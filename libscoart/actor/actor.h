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
#include "msgq.h"

/* User-defined actor class */

class Actor {
public:
    virtual scoa_msg_t& send() = 0;
    virtual void receive(scoa_msg_t&) = 0;
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
