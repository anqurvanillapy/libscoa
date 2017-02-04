#include "../libscoa.hpp"

class Actor {
public:
    virtual scoamsg_t send() = 0;
    virtual void receive() = 0;
private:
    int id;
    Msgq<scoamsg_t> *inbox;
    Msgq<scoamsg_t> *outbox;
}
