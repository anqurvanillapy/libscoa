#include "../scoa.hpp"

class Actor {
public:
    virtual scoamsg_t send() = 0;
    virtual receive() = 0;
private:
    int *addr;
}
