#ifndef __LIBSCOA_H
#define __LIBSCOA_H

typedef struct scoa_msg_t {
    // TODO
} scoa_msg_t;

namespace scoa {
    void spawn(Actor& actor);
    void spawn(uint64_t parent_actor_id, Actor& actor);
    
} // namespace scoa

#endif // !__LIBSCOA_H
