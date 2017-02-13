#ifndef __LIBSCOA_H
#define __LIBSCOA_H
#include <vector>
#include <memory>
#include <boost/any.hpp>
typedef std::array<boost::any> scoa_msg_t;

namespace scoa {
    void spawn(Actor& actor);
    void spawn(uint64_t parent_actor_id, Actor& actor);
    
} // namespace scoa

#endif // !__LIBSCOA_H
