/**
 *  Actor
 *  =====
 *
 *  User-defined actors could implement the pure virtual function be(), namely
 *  behaviour, to specify a custom set of actions, e.g. message sending and
 *  and receiving, by using the public member functions send() and recv(), which
 *  are crucially dispatched by the scheduler.
 */

#ifndef __LIBSCOA_ACTOR_H
#define __LIBSCOA_ACTOR_H

#include <cstdint>
#include <vector>
#include <string>
#include "../libscoa.h"
#include "../sched/sched.h"
#include "msgq.h"
#include "match.h"

enum ActorState
{
    NORMAL,
    ON_RECV,
    ON_AIO
}

class Actor {
public:

    bool        send(uint64_t actor_id, SocaMessage& msg);
    Matcher& recv(std::chrono::milliseconds,string)
    void        be(void *arg) = 0;
    void        scoa_actor_init_(uint64_t actor_id, 
                                MessageQueue<scoa_msg_t>& inbox);

private:
    uint64_t actor_id;

    // Messages in the charge of scheduler
    MessageQueue<SocaMessage&>& inbox;
    
    vector<scoa_msg_t&> tempbox;

    // Dispatched by which scheduler
    Scheduler& scheduler;

    // Id of expected asnyc I/O event
    ActorState state;
    uint64_t   waiting_for;
};

#endif // !__LIBSCOA_ACTOR_H
