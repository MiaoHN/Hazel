#pragma once

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv) {
  hazel::Log::Init();
  HZ_CORE_WARN("Initialized Log!");

  auto app = hazel::CreateApplication();
  app->Run();
  delete app;
}
