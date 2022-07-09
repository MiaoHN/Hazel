#include "application.h"

#include <glad/glad.h>

#include "hazel/events/application_event.h"
#include "hazel/input.h"
#include "hazel/renderer/renderer.h"
#include "log.h"

namespace hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

Application::Application() : _camera(-1.6f, 1.6f, -0.9f, 0.9f) {
  HZ_CORE_ASSERT(!s_instance, "Application already exists!");
  s_instance = this;

  _window = std::unique_ptr<Window>(Window::Create());
  _window->SetEventCallback(BIND_EVENT_FN(OnEvent));

  _imguiLayer = new ImGuiLayer();
  PushOverlay(_imguiLayer);

  _vertexArray.reset(VertexArray::Create());

  float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,  //
      0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,  //
      0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,  //
  };

  std::shared_ptr<VertexBuffer> vertexBuffer;
  vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
  BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                         {ShaderDataType::Float4, "a_Color"}};
  vertexBuffer->SetLayout(layout);
  _vertexArray->AddVertexBuffer(vertexBuffer);

  unsigned int indices[3] = {0, 1, 2};
  std::shared_ptr<IndexBuffer> indexBuffer;
  indexBuffer.reset(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
  _vertexArray->SetIndexBuffer(indexBuffer);

  _squareVA.reset(VertexArray::Create());

  float squareVertices[3 * 4] = {
      -0.75f, -0.75f, 0.0f,  //
      0.75f,  -0.75f, 0.0f,  //
      0.75f,  0.75f,  0.0f,  //
      -0.75f, 0.75f,  0.0f   //
  };

  std::shared_ptr<VertexBuffer> squareVB;
  squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
  _squareVA->AddVertexBuffer(squareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  std::shared_ptr<IndexBuffer> squareIB;
  squareIB.reset(IndexBuffer::Create(squareIndices,
                                     sizeof(squareIndices) / sizeof(uint32_t)));
  _squareVA->SetIndexBuffer(squareIB);

  std::string vertexSrc = R"(
    #version 330 core
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec3 v_Position;
    out vec4 v_Color;

    uniform mat4 u_vp;

		void main() {
		  v_Position = a_Position;
      v_Color = a_Color;
		  gl_Position = u_vp * vec4(a_Position, 1.0);	
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

  std::string blueShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

      uniform mat4 u_vp;

			void main() {
				v_Position = a_Position;
				gl_Position = u_vp * vec4(a_Position, 1.0);	
			}
		)";

  std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

  _blueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    RenderCommand::Clear();

    _camera.SetPosition({0.5f, 0.5f, 0.0f});
    _camera.SetRotation(45.0f);

    Renderer::BeginScene(_camera);

    Renderer::Submit(_blueShader, _squareVA);
    Renderer::Submit(_shader, _vertexArray);

    Renderer::EndScene();

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
