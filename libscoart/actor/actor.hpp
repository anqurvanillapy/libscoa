#ifndef __LIBSCOA_ACTOR_HPP
#define __LIBSCOA_ACTOR_HPP
#include "../libscoa.hpp"

class Actor 
{
public:
    explicit Actor();
    
    Actor(
        uint64_t id, 
        Msgq<scoa_msg_t>& inbox,
        Msgq<scoa_msg_t>& outbox );

    bool send(scoa_msg_t &);
    scoa_msg_t& receive(std::chrono::milliseconds);

private:
    uint64_t scoa_id;
    // inbox and outbox manage by scheduler
    Msgq<scoa_msg_t> &inbox;
    Msgq<scoa_msg_t> &outbox;
}

#endif // !__LIBSCOA_ACTOR_HPP
