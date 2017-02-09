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
#include "../libscoa.h"
#include "../sched/sched.h"
#include "msgq.h"

class Actor {
public:

    bool        send(scoa_msg_t& msg);
    scoa_msg_t& recv(std::chrono::milliseconds timeout);
    void        be(void *arg) = 0;
    void        scoa_actor_init_(uint64_t id, 
                                MessageQueue<scoa_msg_t>& inbox,
                                MessageQueue<scoa_msg_t>& outbox);

private:
    uint64_t scoa_id;

    // Messages in the charge of scheduler
    MessageQueue<scoa_msg_t>& inbox;
    MessageQueue<scoa_msg_t>& outbox;

    // Dispatched by which scheduler
    Scheduler& scheduler;

    // Id of expected asnyc I/O event
    uint64_t   waiting_for;
}

#endif // !__LIBSCOA_ACTOR_H
