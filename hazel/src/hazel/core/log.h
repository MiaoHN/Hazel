#pragma once

#include "hazel/core/core.h"
#include "hzpch.h"
#include "spdlog/spdlog.h"

namespace hazel {

class Log {
 public:
  static void Init();

  inline static Ref<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
  inline static Ref<spdlog::logger>& GetClientLogger() {
    return s_clientLogger;
  }

 private:
  static Ref<spdlog::logger> s_coreLogger;
  static Ref<spdlog::logger> s_clientLogger;
};

}  // namespace hazel

// Core log macros
#define HZ_CORE_TRACE(...) ::hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)  ::hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)  ::hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...) ::hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...) ::hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...) ::hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)  ::hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)  ::hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...) ::hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...) ::hazel::Log::GetClientLogger()->critical(__VA_ARGS__)
