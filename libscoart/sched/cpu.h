#ifndef __LIBSCOA_CPU_H
#define __LIBSCOA_CPU_H

#include <cstdint>
#include "scheduler.h"

/// Count physical/hyper-threading CPUs.
void scoa_cpu_init();

/// Getter of number of CPUs.
uint32_t scoa_cpu_count();

/// Thread assignment to CPUs (pinning).
uint32_t scoa_cpu_assign(uint32_t count, Scheduler& sched, bool nopin,
    bool pinaio);

/// CPU affinity handled ahead of time.
void scoa_cpu_affinity(uint32_t cpu);

#endif // !__LIBSCOA_CPU_H
