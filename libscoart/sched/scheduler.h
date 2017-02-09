/**
 *  Scheduler
 *  =========
 */

#ifndef __LIBSCOA_SCHED_H
#define __LIBSCOA_SCHED_H
#include "../../common/threads.h"
#include "../ds/threadsafe_map.h"
#include "../actor/actor.h"
class Scheduler {
public:
    Scheduler(ThreadSafeMap& global_map);
private:
    scoa_thread_t tid;
    uint32_t cpu;

    bool terminate;

    Actor& current_actor;
    ThreadSafeMap& global_map;
};

#endif // !__LIBSCOA_SCHED_H
