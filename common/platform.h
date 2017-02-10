#ifndef __LIBSCOA_PLATFORM_H
#define __LIBSCOA_PLATFORM_H

/// Macro for extern "C".
#if defined(__cpluscplus)
#   define SCOA_EXTERN_C_BEGIN extern "C" {
#   define SCOA_EXTERN_C_END }
#else
#   define SCOA_EXTERN_C_BEGIN
#   define SCOA_EXTERN_C_END
#endif

/// Platform (Win32, Visual Studio, and further MinGW not supported).
#if defined(__linux__)
#   define IS_LINUX
#elif defined(__FreeBSD__)
#   define IS_FREEBSD
#elif defined(__APPLE__) && defined(__MACH__)
#   define IS_MACOS
#else
#   error PLATFORM NOT SUPPORTED!
#endif

#if defined(IS_LINUX) || defined(IS_MACOS) || defined(IS_FREEBSD)
#   define IS_GCC_OR_CLANG
#   define IS_POSIX_BASED
#endif

/// Data model.
#if defined(__LP64__)
#   define IS_LP64
#else
#   define IS_ILP32
#endif

#if defined(__ILP32__)
#   define int64_t dw_t
#else
#   define __int128_t dw_t
#endif

/// Other utilities.
#include "threads.h"

#endif // !__LIBSCOA_PLATFORM_H
