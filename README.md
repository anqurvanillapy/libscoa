# libscoa

> *Scoa: Self-cultivation of actors.*

`libscoa` is a toy actor model runtime in C++17.

## Usage

- `hello.cc` prints `Hello, world!` to screen.

```cpp
#include "libscoa.h"

class foo_be : public scoa::actor_be<foo_be> {
public:
    auto
    be()
    {
        return scoa::match{
            [&] {
                scoa::asio::printf("Hello, world!\n");
                stop();
            }
        };
    }
};

int
main()
{
    scoa::ctx ctx;
    foo_be foo;

    ctx.spawn_dispatch("foo", &foo_be);
    ctx.start();

    return 0;
}
```

- `pingpong.cc` performs ping-pong playing.

```cpp
#include "libscoa.h"

class pinger : public soca::actor_be<pinger> {
public:
    auto
    be()
    {
        return scoa::match{
            [&] (scoa::ion_t) {
                // ion_t is atom message type.
                if (i_) {
                    send("pong", "ball"_ion);
                    --i_;
                } else {
                    send("pong", 0);
                }
            },
            [&] (auto&&) {
                stop();
            }
        };
    }
private:
    int i_{42}; // 42 balls
};

class ponger : public scoa::actor_be<ponger> {
public:
    auto
    be()
    {
        return scoa::match{
            [&] (scoa::ion_t) {
                send("ping", "ball"_ion);
            },
            [&] (auto&&) {
                send("ping", 0);
                stop();
            }
        };
    }
};

int
main()
{
    scoa::ctx ctx;
    pinger ping;
    ponger pong;

    ctx.spawn_dispatch("ping", &ping, "ball"_ion);
    ctx.spawn("pong", &pong);
    ctx.start();

    return 0;
}
```

## License

MIT
