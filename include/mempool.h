#pragma once

#include "common.h"
#include "lfq.h"

namespace scoa {

class mempool : public lockfreeq {
public:
    mempool() { /* nop */ }
    ~mempool() { /* nop */ }

    // No copy and move.
    mempool(const mempool&) = delete;
    mempool& operator=(const mempool&) = delete;
    mempool(mempool&&) = delete;
    mempool& operator=(mempool&&) = delete;
private:
};

} /* namespace scoa */
