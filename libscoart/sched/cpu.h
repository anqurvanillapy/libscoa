#ifndef __LIBSCOA_CPU_H
#define __LIBSCOA_CPU_H

#include <cstdint>
#include "sched.h"

/// Count physical/hyper-threading CPUs
void scoa_cpu_init();

/// Getter of number of CPUs
uint32_t scoa_cpu_count();

/// Thread assignment to CPUs (pinning)
uint32_t scoa_cpu_assign(uint32_t count, Scheduler& sched, bool nopin,
    bool pinaio);

/// TODO: CPU affinity and more.

#endif // !__LIBSCOA_CPU_H
