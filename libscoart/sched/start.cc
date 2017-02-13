/**
 *  Scheduling
 *  ==========
 *
 *  The entry point of scheduling, hence the start of the libscoa runtime.
 */

#include "../libscoa.h"
#include "cpu.h"

namespace scoa {
    void
    scoa_init(uint32_t threads_num, int opt)
    {
        bool nopin      = (opt & 1 << 0) ? true: false;
        bool aiopin     = (opt & 1 << 1) ? true: false;
        bool noyield    = (opt & 1 << 2) ? true: false;

        if (threads_num == 0) threads_num = scoa_cpu_count();

        // TODO: initialize the schedulers and start the run.
    }

    void
    spawn(Actor& actor)
    {
        // TODO
    }
}
