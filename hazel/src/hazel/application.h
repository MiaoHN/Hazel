#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "hazel/core.h"
#include "hazel/events/application_event.h"
#include "hazel/imgui/imgui_layer.h"
#include "hazel/layer_stack.h"
#include "hazel/renderer/buffer.h"
#include "hazel/renderer/orthographic_camera.h"
#include "hazel/renderer/shader.h"
#include "hazel/renderer/vertex_array.h"
#include "hazel/window.h"
#include "hzpch.h"

namespace hazel {

class HAZEL_API Application {
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

  std::shared_ptr<Shader> _shader;
  std::shared_ptr<VertexArray> _vertexArray;

  std::shared_ptr<Shader> _blueShader;
  std::shared_ptr<VertexArray> _squareVA;

  OrthoGraphicCamera _camera;

 private:
  static Application* s_instance;
};

// To be defined in client
Application* CreateApplication();

}  // namespace hazel

#endif  // __APPLICATION_H__