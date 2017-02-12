#include "aio.h"

void
AsyncIO::start()
{
    
}

void
AsyncIO::stop()
{

}

void
AsyncIO::final()
{
    facility->terminated.store(true, memory_order_relaxed);
    evenfd_write(facility->evfd, 1);
}
