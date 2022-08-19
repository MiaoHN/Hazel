#include <hazel.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "platform/opengl/opengl_shader.h"

class ExampleLayer : public hazel::Layer {
 public:
  ExampleLayer()
      : Layer("Example"), cameraController_(1280.0f / 720.0f, false) {
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

    _shader = hazel::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

    _flatColorShader = hazel::Shader::Create(
        "FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
    auto textureShader =
        shaderLibrary_.Load("Texture", "assets/shaders/texture.glsl");

    _texture = hazel::Texture2D::Create("assets/textures/checker_board.png");
    _chernoLogoTexture =
        hazel::Texture2D::Create("assets/textures/cherno_logo.png");

    std::dynamic_pointer_cast<hazel::OpenGLShader>(textureShader)->Bind();
    std::dynamic_pointer_cast<hazel::OpenGLShader>(textureShader)
        ->UploadUniformInt("u_texture", 0);
  }

  void OnUpdate(hazel::Timestep ts) override {
    // Update
    cameraController_.onUpdate(ts);

    // Render
    hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    hazel::RenderCommand::Clear();

    hazel::Renderer::BeginScene(cameraController_.GetCamera());

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

    auto textureShader = shaderLibrary_.Get("Texture");

    _texture->Bind();
    hazel::Renderer::Submit(textureShader, _squareVA,
                            glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    _chernoLogoTexture->Bind();
    hazel::Renderer::Submit(textureShader, _squareVA,
                            glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // hazel::Renderer::Submit(_shader, _vertexArray);

    hazel::Renderer::EndScene();
  }

  void OnImGuiRender() override {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Squire Color", glm::value_ptr(_squareColor));
    ImGui::End();
  }

  void OnEvent(hazel::Event& event) override {
    cameraController_.onEvent(event);
  }

 private:
  hazel::ShaderLibrary shaderLibrary_;
  hazel::Ref<hazel::Shader> _shader;
  hazel::Ref<hazel::VertexArray> _vertexArray;

  hazel::Ref<hazel::Shader> _flatColorShader;
  hazel::Ref<hazel::VertexArray> _squareVA;

  hazel::Ref<hazel::Texture2D> _texture, _chernoLogoTexture;

  hazel::OrthographicCameraController cameraController_;
  glm::vec3 _squareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public hazel::Application {
 public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}

 private:
};

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }