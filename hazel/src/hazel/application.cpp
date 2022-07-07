#include "application.h"

#include <glad/glad.h>

#include "hazel/events/application_event.h"
#include "log.h"

namespace hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

Application::Application() {
  HZ_CORE_ASSERT(!s_instance, "Application already exists!");
  s_instance = this;

  _window = std::unique_ptr<Window>(Window::Create());
  _window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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

void Application::PushLayer(Layer* layer) {
  _layerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
  _layerStack.PushOverlay(layer);
  layer->OnAttach();
}

void Application::Run() {
  while (_running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer* layer : _layerStack) {
      layer->OnUpdate();
    }
    _window->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
  _running = false;
  return true;
}

}  // namespace hazel
