#pragma once

#include "hazel/core/core.h"
#include "hazel/core/layer_stack.h"
#include "hazel/core/time_step.h"
#include "hazel/core/window.h"
#include "hazel/events/application_event.h"
#include "hazel/events/event.h"
#include "hazel/imgui/imgui_layer.h"
#include "hzpch.h"

int main(int argc, char** argv);

namespace hazel {

class Application {
 public:
  Application();
  virtual ~Application();

  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

  inline Window& GetWindow() { return *window_; }

  inline static Application& Get() { return *s_instance; }

 private:
  void Run();

  bool OnWindowClose(WindowCloseEvent& e);
  bool OnWindowResize(WindowResizeEvent& e);

 private:
  std::unique_ptr<Window> window_;

  ImGuiLayer* imguiLayer_;
  bool        running_   = true;
  bool        minimized_ = false;
  LayerStack  layerStack_;

  float _lastFrameTime = 0.0f;

 private:
  static Application* s_instance;
  friend int ::main(int argc, char** argv);
};

// To be defined in client
Application* CreateApplication();

}  // namespace hazel
