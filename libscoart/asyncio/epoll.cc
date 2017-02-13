#include "asyncio.h"

#ifdef AIO_USE_EPOLL

AsyncIO::AsyncIO()
{
    // Create epoll instance.
    epfd = epoll_create1(EPOLL_CLOEXEC);
    // eventfd for breaking epoll loop.
    evfd = eventfd(0, EFD_NONBLOCK);

    if (epfd < 1 || evfd < 1) return;

    // Set up epoll configuration
    struct epoll_event epconfig;
    epconfig.data.ptr = facility;
    epconfig.events = EPOLLIN | EPOLLRDHUP | EPOLLET;

    epoll_ctl(facility.epfd, EPOLL_CTL_ADD, facility.evfd, &epconfig);
}

~AsyncIO::AsyncIO()
{
    terminated.store(true, memory_order_relaxed);
    evenfd_write(evfd, 1);

    delete aio_thread;
}

void
AsyncIO::thread_func()
{
    while (terminated.load(memory_order_relaxed)) {
        
    }
}

#endif // AIO_USE_EPOLL
