#include "application.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "hazel/events/application_event.h"
#include "hazel/input.h"
#include "log.h"

namespace hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

Application::Application() {
  HZ_CORE_ASSERT(!s_instance, "Application already exists!");
  s_instance = this;

  _window = std::unique_ptr<Window>(Window::Create());
  _window->SetEventCallback(BIND_EVENT_FN(OnEvent));

  _imguiLayer = new ImGuiLayer();
  PushOverlay(_imguiLayer);
}

Application::~Application() {}

void Application::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

  for (auto it = _layerStack.end(); it != _layerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.handled) {
      break;
    }
  }
}

void Application::PushLayer(Layer* layer) { _layerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { _layerStack.PushOverlay(layer); }

void Application::Run() {
  while (_running) {
    float time = (float)glfwGetTime();
    Timestep timestep = time - _lastFrameTime;
    _lastFrameTime = time;
    for (Layer* layer : _layerStack) {
      layer->OnUpdate(timestep);
    }

    _imguiLayer->Begin();
    for (Layer* layer : _layerStack) {
      layer->OnImGuiRender();
    }
    _imguiLayer->End();

    _window->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
  _running = false;
  return true;
}

}  // namespace hazel
