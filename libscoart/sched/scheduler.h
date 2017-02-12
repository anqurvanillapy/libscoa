/**
 *  Scheduler
 *  =========
 */

#ifndef __LIBSCOA_SCHEDULER_H
#define __LIBSCOA_SCHEDULER_H

class Scheduler {
public:
    Scheduler();

    std::thread* sched_thread;
};

#endif // !__LIBSCOA_SCHEDULER_H
