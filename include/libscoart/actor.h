#pragma once

#include "common.h"
#include "lfq.h"

namespace scoa {

class inbox : public lockfreeq {
public:
    inbox() { /* nop */ }
    ~inbox() { /* nop */ }

    // No copy and move.
    inbox(const inbox&) = delete;
    inbox& operator=(const inbox&) = delete;
    inbox(inbox&&) = delete;
    inbox& operator=(inbox&&) = delete;
private:
};

class outbox : public lockfreeq {
public:
    outbox() { /* nop */ }
    ~outbox() { /* nop */ }

    // No copy and move.
    outbox(const outbox&) = delete;
    outbox& operator=(const outbox&) = delete;
    outbox(outbox&&) = delete;
    outbox& operator=(outbox&&) = delete;
private:
};

class actor {
public:
    actor() { /* nop */ }
    virtual ~actor() { /* nop */ }

    // No copy and move.
    actor(const actor&) = delete;
    actor& operator=(const actor&) = delete;
    actor(actor&&) = delete;
    actor& operator=(actor&&) = delete;

    friend class init_actor;
private:
    inbox inbox_;
    outbox outbox_;
};

/// init_actor is a special actor for starting libscoa runtime and create a
/// actor tree as the root.

class init_actor : public actor {
public:
  init_actor() { /* nop */ }
  ~init_actor() { /* nop */ }

  // No copy and move.
  init_actor(const init_actor&) = delete;
  init_actor& operator=(const init_actor&) = delete;
  init_actor(init_actor&&) = delete;
  init_actor& operator=(init_actor&&) = delete;
private:
  using actor::inbox_;
  using actor::outbox_;
};

} /* namespace scoa */
