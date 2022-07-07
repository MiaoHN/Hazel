#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "hazel/core.h"
#include "hazel/events/application_event.h"
#include "hazel/window.h"
#include "hzpch.h"

namespace hazel {

class HAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

  bool OnWindowClose(WindowCloseEvent& e);

 private:
  std::unique_ptr<Window> _window;
  bool _running = true;
};

// To be defined in client
Application* CreateApplication();

}  // namespace hazel

#endif  // __APPLICATION_H__