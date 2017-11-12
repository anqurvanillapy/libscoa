#pragma once

#include <cassert>
#include <cstdint>
#include <csetjmp>

#include <memory>
#include <string>
#include <list>
#include <vector>
#include <functional>

namespace scoa {

#define SCOA_STACKSIZ (1024 * 1024)
#define SCOA_MATCHFN_TYPE void(void*)

} /* namespace scoa */
