#include "aio.h"

#ifdef AIO_USE_EPOLL

#include <sys/epoll.h>
#include <sys/eventfd.h>

typedef struct scoa_aio_facility_t {
    int epfd;
    int evfd;
    struct epoll_event events[MAX_EVENTS];
    std::atomic_bool terminated;
} scoa_aio_facility_t;

AsyncIO::AsyncIO()
{
    facility = new scoa_aio_facility_t{};   // FIXME: struct value init

    // Create epoll instance.
    facility->epfd = epoll_create1(EPOLL_CLOEXEC);
    // eventfd for breaking epoll loop.
    facility->evfd = eventfd(0, EFD_NONBLOCK);

    if (facility->epfd < 1 || facility->evfd < 1) return;

    struct epoll_event epconfig;
    epconfig.data.ptr = facility;
    epconfig.events = EPOLLIN | EPOLLRDHUP | EPOLLET;

    epoll_ctl(facility->epfd, EPOLL_CTL_ADD, facility->evfd, &epconfig);
}

/// Create a thread for AsyncIO with epoll mechanism.
std::thread
scoa_aio_facility_dispatch([scoa_aio_facility_t* facility] {
    while (!facility->terminated.load(memory_order_relaxed)) {
        // TOOD: epoll loop
    }
});

#endif // AIO_USE_EPOLL
