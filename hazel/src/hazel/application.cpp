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

  std::string vertexSrc = R"(
    #version 330 core
		layout(location = 0) in vec3 a_Position;

		out vec3 v_Position;

		void main() {
		  v_Position = a_Position;
		  gl_Position = vec4(a_Position, 1.0);	
		}
  )";

  std::string fragmentSrc = R"(
		#version 330 core
		layout(location = 0) out vec4 color;

		in vec3 v_Position;

		void main() {
		  color = vec4(v_Position * 0.5 + 0.5, 1.0);
		}
	)";

  _shader.reset(new Shader(vertexSrc, fragmentSrc));
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

    _shader->Bind();
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
