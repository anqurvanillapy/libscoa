#include "aio.h"

static AsyncIO running_aio;

AsyncIO::AsyncIO()
{
    // TODO: return specific mechanism and do the initialization.
    facility = new AIOFacility;
}

void
AsyncIO::start()
{
    
}

void
AsyncIO::stop()
{

}
