#include "aio.h"

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

void
AsyncIO::final()
{
    terminated.store(true, memory_order_relaxed);
    evenfd_write(evfd, 1);
}

/// Thread declaration for creating epoll loop.
void
operator() ()
{
    while (terminated.load(memory_order_relaxed)) {
        // Timeout -1 to make epoll_wait block indefinitely
        int nfds = epoll_wait(f.epfd, f.events, MAX_EVENTS, -1);
        int i;

        for (i = 0; i < nfds; ++i) {
            // TODO
        }
    }
}

#endif // AIO_USE_EPOLL
