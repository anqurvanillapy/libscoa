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

class Actor {
public:
    virtual scoa_msg_t& send();
    virtual void receive(scoa_msg_t&);

private:
    uint64_t id;
    Msgq<scoa_msg_t> *inbox;
    Msgq<scoa_msg_t> *outbox;
}

class ActorPrototype { };

#endif // !__LIBSCOA_ACTOR_H
