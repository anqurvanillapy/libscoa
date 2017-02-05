#ifndef __LIBSCOA_ASYNCIO_H
#define __LIBSCOA_ASYNCIO_H

enum AsyncIOEvent
{
  ASIO_DISPOSABLE = 0,
  ASIO_READ  = 1 << 0,
  ASIO_WRITE = 1 << 1,
  ASIO_TIMER = 1 << 2,
  ASIO_SIGNAL = 1 << 3,
  ASIO_ONESHOT = 1 << 8,
  ASIO_DESTROYED = (uint32_t)-1
};


#endif