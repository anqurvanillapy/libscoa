#include "aio.h"
#include <sys/epoll.h>

typedef struct scoa_aio_facility {
    int epfd;
    struct epoll_event events[MAX_EVENTS];
} scoa_aio_facility;
