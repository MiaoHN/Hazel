#include <hazel.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "platform/opengl/opengl_shader.h"

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

    hazel::Ref<hazel::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
    hazel::BufferLayout layout = {{hazel::ShaderDataType::Float3, "a_Position"},
                                  {hazel::ShaderDataType::Float4, "a_Color"}};
    vertexBuffer->SetLayout(layout);
    _vertexArray->AddVertexBuffer(vertexBuffer);

    unsigned int indices[3] = {0, 1, 2};
    hazel::Ref<hazel::IndexBuffer> indexBuffer;
    indexBuffer.reset(hazel::IndexBuffer::Create(
        indices, sizeof(indices) / sizeof(unsigned int)));
    _vertexArray->SetIndexBuffer(indexBuffer);

    _squareVA.reset(hazel::VertexArray::Create());

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  //
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  //
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  //
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  //
    };

    hazel::Ref<hazel::VertexBuffer> squareVB;
    squareVB.reset(
        hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{hazel::ShaderDataType::Float3, "a_Position"},
                         {hazel::ShaderDataType::Float2, "a_TexCoord"}});
    _squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    hazel::Ref<hazel::IndexBuffer> squareIB;
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
    uniform mat4 u_transform;

		void main() {
		  v_Position = a_Position;
      v_Color = a_Color;
		  gl_Position = u_vp * u_transform * vec4(a_Position, 1.0);	
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

    _shader.reset(hazel::Shader::Create(vertexSrc, fragmentSrc));

    std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

      uniform mat4 u_vp;
      uniform mat4 u_transform;

			void main() {
				v_Position = a_Position;
				gl_Position = u_vp * u_transform * vec4(a_Position, 1.0);	
			}
		)";

    std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

      uniform vec3 u_color;

			void main() {
        color = vec4(u_color, 1.0f);
			}
		)";

    _flatColorShader.reset(hazel::Shader::Create(flatColorShaderVertexSrc,
                                                 flatColorShaderFragmentSrc));

    std::string textureShaderVertexSrc = R"(
      #version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_vp;
			uniform mat4 u_transform;

			out vec2 v_texCoord;

			void main() {
				v_texCoord = a_TexCoord;
				gl_Position = u_vp * u_transform * vec4(a_Position, 1.0);	
			}
    )";

    std::string textureShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			in vec2 v_texCoord;
			
			uniform sampler2D u_texture;

			void main() {
				color = texture(u_texture, v_texCoord);
			}
		)";

    _textureShader.reset(hazel::Shader::Create(textureShaderVertexSrc,
                                               textureShaderFragmentSrc));

    _texture = hazel::Texture2D::Create("assets/textures/checker_board.png");

    std::dynamic_pointer_cast<hazel::OpenGLShader>(_textureShader)->Bind();
    std::dynamic_pointer_cast<hazel::OpenGLShader>(_textureShader)
        ->UploadUniformInt("u_texture", 0);
  }

  void OnUpdate(hazel::Timestep ts) override {
    if (hazel::Input::IsKeyPressed(HZ_KEY_A)) {
      _cameraPosition.x -= _cameraMoveSpeed * ts;
    } else if (hazel::Input::IsKeyPressed(HZ_KEY_D)) {
      _cameraPosition.x += _cameraMoveSpeed * ts;
    }

    if (hazel::Input::IsKeyPressed(HZ_KEY_W)) {
      _cameraPosition.y += _cameraMoveSpeed * ts;
    } else if (hazel::Input::IsKeyPressed(HZ_KEY_S)) {
      _cameraPosition.y -= _cameraMoveSpeed * ts;
    }

    if (hazel::Input::IsKeyPressed(HZ_KEY_Q)) {
      _cameraRotation -= _cameraRotationSpeed * ts;
    } else if (hazel::Input::IsKeyPressed(HZ_KEY_E)) {
      _cameraRotation += _cameraRotationSpeed * ts;
    }

    hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    hazel::RenderCommand::Clear();

    _camera.SetPosition(_cameraPosition);
    _camera.SetRotation(_cameraRotation);

    hazel::Renderer::BeginScene(_camera);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<hazel::OpenGLShader>(_flatColorShader)->Bind();
    std::dynamic_pointer_cast<hazel::OpenGLShader>(_flatColorShader)
        ->UploadUniformFloat3("u_color", _squareColor);

    for (int y = 0; y < 20; y++) {
      for (int x = 0; x < 20; x++) {
        glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        hazel::Renderer::Submit(_flatColorShader, _squareVA, transform);
      }
    }

    _texture->Bind();
    hazel::Renderer::Submit(_textureShader, _squareVA,
                            glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // hazel::Renderer::Submit(_shader, _vertexArray);

    hazel::Renderer::EndScene();
  }

  void OnImGuiRender() override {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Squire Color", glm::value_ptr(_squareColor));
    ImGui::End();
  }

  void OnEvent(hazel::Event& event) override {}

 private:
  hazel::Ref<hazel::Shader> _shader;
  hazel::Ref<hazel::VertexArray> _vertexArray;

  hazel::Ref<hazel::Shader> _flatColorShader, _textureShader;
  hazel::Ref<hazel::VertexArray> _squareVA;

  hazel::Ref<hazel::Texture2D> _texture;

  hazel::OrthoGraphicCamera _camera;
  glm::vec3 _cameraPosition;

  float _cameraMoveSpeed = 5.0f;

  float _cameraRotation = 0.0f;
  float _cameraRotationSpeed = 180.0f;

  glm::vec3 _squareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public hazel::Application {
 public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}

 private:
};

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }