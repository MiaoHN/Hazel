#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv) {
  hazel::Log::Init();
  HZ_CORE_WARN("Initialized Log!");
  int a = 5;
  HZ_CLIENT_INFO("Hello! Var={0}", a);

  auto app = hazel::CreateApplication();
  app->Run();
  delete app;
}

#endif  // __ENTRY_POINT_H__