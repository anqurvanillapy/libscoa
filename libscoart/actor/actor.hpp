#ifndef __LIBSCOA_ACTOR_HPP
#define __LIBSCOA_ACTOR_HPP
#include <ctime>
#include "../libscoa.hpp"

class Actor {
public:
    bool send(){};
    &scoa_msg_t receive(std::time_t){}
private:
    int id;

    virtual scoa_msg_t& send() = 0;
    virtual void receive(scoa_msg_t&) = 0;
private:
    uint64_t id;
    Msgq<scoa_msg_t> *inbox;
    Msgq<scoa_msg_t> *outbox;
}

#endif // !__LIBSCOA_ACTOR_HPP
