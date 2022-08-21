#pragma once

#include "hazel/core/core.h"

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv) {
  hazel::Log::Init();

  HZ_PROFILE_BEGIN_SESSION("Startup", "hazel_profile_startup.json");
  auto app = hazel::CreateApplication();
  HZ_PROFILE_END_SESSION();

  HZ_PROFILE_BEGIN_SESSION("Runtime", "hazel_profile_runtime.json");
  app->Run();
  HZ_PROFILE_END_SESSION();

  HZ_PROFILE_BEGIN_SESSION("Shutdown", "hazel_profile_shutdown.json");
  delete app;
  HZ_PROFILE_END_SESSION();
}
