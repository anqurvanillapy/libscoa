#include "aio.h"

static AsyncIO* running_aio = NULL;
static std::thread* scoa_aio_thread = NULL;

void
scoa_aio_start()
{
    running_aio = new AsyncIO();
    scoa_aio_thread = new std::thread(running_io);
}

void
AsyncIO::stop()
{
    if (running_aio != NULL) {
        running_aio.final();
        scoa_aio_thread->join();

        delete scoa_aio_thread;
        scoa_aio_thread = NULL;
        delete running_aio;
        running_aio = NULL;
    }
}
