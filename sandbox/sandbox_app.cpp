#include <hazel.h>

#include "imgui.h"

class ExampleLayer : public hazel::Layer {
 public:
  ExampleLayer()
      : Layer("Example"),
        _camera(-1.6f, 1.6f, -0.9f, 0.9f),
        _cameraPosition(0.0f) {
    _vertexArray.reset(hazel::VertexArray::Create());

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,  //
        0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,  //
        0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,  //
    };

    std::shared_ptr<hazel::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
    hazel::BufferLayout layout = {{hazel::ShaderDataType::Float3, "a_Position"},
                                  {hazel::ShaderDataType::Float4, "a_Color"}};
    vertexBuffer->SetLayout(layout);
    _vertexArray->AddVertexBuffer(vertexBuffer);

    unsigned int indices[3] = {0, 1, 2};
    std::shared_ptr<hazel::IndexBuffer> indexBuffer;
    indexBuffer.reset(hazel::IndexBuffer::Create(
        indices, sizeof(indices) / sizeof(unsigned int)));
    _vertexArray->SetIndexBuffer(indexBuffer);

    _squareVA.reset(hazel::VertexArray::Create());

    float squareVertices[3 * 4] = {
        -0.75f, -0.75f, 0.0f,  //
        0.75f,  -0.75f, 0.0f,  //
        0.75f,  0.75f,  0.0f,  //
        -0.75f, 0.75f,  0.0f   //
    };

    std::shared_ptr<hazel::VertexBuffer> squareVB;
    squareVB.reset(
        hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{hazel::ShaderDataType::Float3, "a_Position"}});
    _squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<hazel::IndexBuffer> squareIB;
    squareIB.reset(hazel::IndexBuffer::Create(
        squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

    _shader.reset(new hazel::Shader(vertexSrc, fragmentSrc));

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

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

    _blueShader.reset(
        new hazel::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
  }

  void OnUpdate(hazel::Timestep ts) override {
    if (hazel::Input::IsKeyPressed(HZ_KEY_A)) {
      _cameraPosition.x += _cameraMoveSpeed * ts;
    } else if (hazel::Input::IsKeyPressed(HZ_KEY_D)) {
      _cameraPosition.x -= _cameraMoveSpeed * ts;
    }

    if (hazel::Input::IsKeyPressed(HZ_KEY_W)) {
      _cameraPosition.y -= _cameraMoveSpeed * ts;
    } else if (hazel::Input::IsKeyPressed(HZ_KEY_S)) {
      _cameraPosition.y += _cameraMoveSpeed * ts;
    }

    if (hazel::Input::IsKeyPressed(HZ_KEY_Q)) {
      _cameraRotation += _cameraRotationSpeed * ts;
    } else if (hazel::Input::IsKeyPressed(HZ_KEY_E)) {
      _cameraRotation -= _cameraRotationSpeed * ts;
    }

    hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    hazel::RenderCommand::Clear();

    _camera.SetPosition(_cameraPosition);
    _camera.SetRotation(_cameraRotation);

    hazel::Renderer::BeginScene(_camera);

    hazel::Renderer::Submit(_blueShader, _squareVA);
    hazel::Renderer::Submit(_shader, _vertexArray);

    hazel::Renderer::EndScene();
  }

  void OnImGuiRender() override {}

  void OnEvent(hazel::Event& event) override {}

 private:
  std::shared_ptr<hazel::Shader> _shader;
  std::shared_ptr<hazel::VertexArray> _vertexArray;

  std::shared_ptr<hazel::Shader> _blueShader;
  std::shared_ptr<hazel::VertexArray> _squareVA;

  hazel::OrthoGraphicCamera _camera;
  glm::vec3 _cameraPosition;

  float _cameraMoveSpeed = 5.0f;

  float _cameraRotation = 0.0f;
  float _cameraRotationSpeed = 180.0f;
};

class Sandbox : public hazel::Application {
 public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}

 private:
};

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }