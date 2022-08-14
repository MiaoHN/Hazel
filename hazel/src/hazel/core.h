#ifndef __CORE_H__
#define __CORE_H__

#include <memory>
#ifndef HZ_PLATFORM_WINDOWS
#include <csignal>
#endif

#ifdef HZ_PLATFORM_WINDOWS
#ifdef HZ_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif
#else
#define HAZEL_API
#endif

#ifdef HZ_DEBUG
#define HZ_ENABLE_ASSERTS
#endif

#ifdef HZ_ENABLE_ASSERTS

#ifdef HZ_PLATFORM_WINDOWS
#define HZ_ASSERT(x, ...)                             \
  {                                                   \
    if (!x) {                                         \
      HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                 \
    }                                                 \
  }
#define HZ_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!x) {                                              \
      HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                      \
    }                                                      \
  }
#else
#define HZ_ASSERT(x, ...)                             \
  {                                                   \
    if (!x) {                                         \
      HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      raise(SIGTRAP);                                 \
    }                                                 \
  }
#define HZ_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!x) {                                              \
      HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      raise(SIGTRAP);                                      \
    }                                                      \
  }

#endif
#else
#define HZ_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace hazel {

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

}  // namespace hazel

#endif  // __CORE_H__