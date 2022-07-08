#include "application.h"

#include <glad/glad.h>

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

  glGenVertexArrays(1, &_vertexArray);
  glBindVertexArray(_vertexArray);

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

  float vertices[3 * 3] = {
      -0.5f, -0.5f, 0.0f,  //
      0.5f,  -0.5f, 0.0f,  //
      0.0f,  0.5f,  0.0f,  //
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  glGenBuffers(1, &_indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

  unsigned int indices[3] = {0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
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
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(_vertexArray);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    for (Layer* layer : _layerStack) {
      layer->OnUpdate();
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
