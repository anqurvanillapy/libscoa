libscoa
=======

**S**elf-**c**ultivation **o**f **a**ctors.

**Warning:** Work in progress.

Prerequisites
-------------

- `libuv`

### For dev

- `gtest`

Usage
-----

*(These examples here are liable to change, due to the current development.)*

- `hello.cc` to print `Hello, world!` using libscoa's asynchronous I/O API:

```cpp
#include "libscoa.h"

class Foo : public Actor {
public:
    // Specify a behaviour.
    void
    be()
    {
        // Use scoa::acout (async character output) to print the message.
        scoa::acout << "Hello, world!" << std::endl;
    }
};

int
main(int argc, const char *argv[])
{
    // Default number of threads and other options.
    scoa::init(SCOA_THREADS_NUM, SCOA_DEFAULT);

    // Spawn the actor.
    scoa::spawn(Foo);

    return 0;
}
```

- `match.cc` to match and catch the received messages:

```cpp
#include "libscoa.h"

class Foo : public Actor {
public:
    void
    be()
    {
        std::string name = "John";
        send(Bar) << "hi" << &name;
    }
};

class Bar : public Actor {
public:
    void
    be()
    {
        std::string name;

        // Match "hi", catch a name, and fputs asynchronously the received name.
        recv << "hi" >> &name .fn([=] {
            scoa::afputs(stdout, &name);
        });
    }
};

int
main(int argc, const char *argv[])
{
    scoa::init(SCOA_THREADS_NUM, SCOA_DEFAULT);

    // Spawn the actors.
    scoa::spawn(Foo);
    scoa::spawn(Bar);

    return 0;
}
```

License
-------

MIT
