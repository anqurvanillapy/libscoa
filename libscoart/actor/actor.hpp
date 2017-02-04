#include <ctime>
#include "../libscoa.hpp"

class Actor {
public:
    bool send(){
        //TODO
    };
    &scoa_msg_t receive(std::time_t){
        //TODO
    }
private:
    int id;
    Msgq<scoa_msg_t> *inbox;
    Msgq<scoa_msg_t> *outbox;
}
