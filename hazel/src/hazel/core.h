#ifndef __CORE_H__
#define __CORE_H__

#ifdef HZ_PLATFORM_WINDOWS
#ifdef HZ_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif
#else
#define HAZEL_API
#endif

#define BIT(x) (1 << x)

#endif  // __CORE_H__