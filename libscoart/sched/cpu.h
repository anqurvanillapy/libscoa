#ifndef __LIBSCOA_CPU_H
#define __LIBSCOA_CPU_H

#include <cstdint>
#include "scheduler.h"

/// Getter of number of CPUs.
uint32_t scoa_cpu_count();

/// Thread assignment to CPUs (pinning).
bool scoa_cpu_assign(uint32_t count, std::thread& thread, bool nopin,
    bool pinaio);

#endif // !__LIBSCOA_CPU_H
