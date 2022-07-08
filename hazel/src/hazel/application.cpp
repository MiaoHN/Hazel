#include "application.h"

#include <glad/glad.h>

#include "hazel/events/application_event.h"
#include "hazel/input.h"
#include "log.h"

namespace hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

static unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
    case hazel::ShaderDataType::Float:
      return GL_FLOAT;
    case hazel::ShaderDataType::Float2:
      return GL_FLOAT;
    case hazel::ShaderDataType::Float3:
      return GL_FLOAT;
    case hazel::ShaderDataType::Float4:
      return GL_FLOAT;
    case hazel::ShaderDataType::Mat3:
      return GL_FLOAT;
    case hazel::ShaderDataType::Mat4:
      return GL_FLOAT;
    case hazel::ShaderDataType::Int:
      return GL_INT;
    case hazel::ShaderDataType::Int2:
      return GL_INT;
    case hazel::ShaderDataType::Int3:
      return GL_INT;
    case hazel::ShaderDataType::Int4:
      return GL_INT;
    case hazel::ShaderDataType::Bool:
      return GL_BOOL;
  }

  HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

Application::Application() {
  HZ_CORE_ASSERT(!s_instance, "Application already exists!");
  s_instance = this;

  _window = std::unique_ptr<Window>(Window::Create());
  _window->SetEventCallback(BIND_EVENT_FN(OnEvent));

  _imguiLayer = new ImGuiLayer();
  PushOverlay(_imguiLayer);

  glGenVertexArrays(1, &_vertexArray);
  glBindVertexArray(_vertexArray);

  float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,  //
      0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,  //
      0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,  //
  };

  _vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

  {
    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                           {ShaderDataType::Float4, "a_Color"}};

    _vertexBuffer->SetLayout(layout);
  }

  unsigned int index = 0;
  const auto& layout = _vertexBuffer->GetLayout();
  for (const auto& element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride(), (const void*)element.offset);
    index++;
  }

  unsigned int indices[3] = {0, 1, 2};
  _indexBuffer.reset(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

  std::string vertexSrc = R"(
    #version 330 core
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec3 v_Position;
    out vec4 v_Color;

		void main() {
		  v_Position = a_Position;
      v_Color = a_Color;
		  gl_Position = vec4(a_Position, 1.0);	
		}
  )";

  std::string fragmentSrc = R"(
		#version 330 core
		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main() {
		  color = vec4(v_Position * 0.5 + 0.5, 1.0);
      color = v_Color;
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
    glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT,
                   nullptr);

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
