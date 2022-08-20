#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv) {
  hazel::Log::Init();
  HZ_CORE_WARN("Initialized Log!");

  auto app = hazel::CreateApplication();
  app->Run();
  delete app;
}

#endif  // __ENTRY_POINT_H__