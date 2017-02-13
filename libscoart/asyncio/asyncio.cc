#include "asyncio.h"

static AsyncIO* scoa_aio = NULL;

void
scoa_aio_start(uint32_t cpu)
{
    scoa_aio = new AsyncIO(cpu);
    scoa_aio.aio_thread = new std::thread(scoa_aio.thread_func, scoa_aio);
}

void
scoa_aio_stop()
{
    if (scoa_aio != NULL) {
        scoa_aio.aio_thread->join();

        delete scoa_aio;
        scoa_aio = NULL;
    }
}
