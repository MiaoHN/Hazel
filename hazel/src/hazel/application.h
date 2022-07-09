#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "hazel/core.h"
#include "hazel/core/time_step.h"
#include "hazel/events/application_event.h"
#include "hazel/imgui/imgui_layer.h"
#include "hazel/layer_stack.h"
#include "hazel/window.h"
#include "hzpch.h"

namespace hazel {

class Application {
 public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

  inline Window& GetWindow() { return *_window; }

  inline static Application& Get() { return *s_instance; }

 private:
  bool OnWindowClose(WindowCloseEvent& e);

 private:
  std::unique_ptr<Window> _window;
  ImGuiLayer* _imguiLayer;
  bool _running = true;
  LayerStack _layerStack;

  float _lastFrameTime = 0.0f;

 private:
  static Application* s_instance;
};

// To be defined in client
Application* CreateApplication();

}  // namespace hazel

#endif  // __APPLICATION_H__