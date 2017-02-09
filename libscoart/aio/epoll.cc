#include "aio.h"

#ifdef AIO_USE_EPOLL

#include <sys/epoll.h>


typedef struct scoa_aio_facility {
    int epfd;
    struct epoll_event events[MAX_EVENTS];
} scoa_aio_facility;

#endif // AIO_USE_EPOLL
