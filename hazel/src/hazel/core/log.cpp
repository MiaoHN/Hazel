#include "hazel/core/log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace hazel {

Ref<spdlog::logger> Log::s_coreLogger;
Ref<spdlog::logger> Log::s_clientLogger;

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  s_coreLogger = spdlog::stdout_color_mt("HAZEL");
  s_coreLogger->set_level(spdlog::level::trace);

  s_clientLogger = spdlog::stdout_color_mt("APP");
  s_clientLogger->set_level(spdlog::level::trace);
}

}  // namespace hazel
