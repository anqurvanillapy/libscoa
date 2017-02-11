#include "aio.h"

#ifdef AIO_USE_EPOLL

#include <sys/epoll.h>

AIOFacility::AIOFacility()
{
    // Create epoll instance.
    this->epfd = epoll_create1(EPOLL_CLOEXEC);
}

bool
AIOFacility::destroy()
{

}

DECLARE_THREAD_FUNC(scoa_aio_facility_dispatch)
{

}

#endif // AIO_USE_EPOLL
