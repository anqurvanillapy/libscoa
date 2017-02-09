/**
 *  Scheduler
 *  =========
 */

#ifndef __LIBSCOA_SCHED_H
#define __LIBSCOA_SCHED_H
#include "../../common/threads.h"
#include "../ds/threadsafe_map.h"

class Scheduler {
public:
    Scheduler(ThreadSafeMap& global_map);
private:
    scoa_thread_t tid;
    uint32_t cpu;
    bool terminate;
    ThreadSafeMap& global_map;
};

#endif // !__LIBSCOA_SCHED_H
