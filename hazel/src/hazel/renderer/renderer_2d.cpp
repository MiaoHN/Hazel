#include "hazel/renderer/renderer_2d.h"

#include <glm/gtc/matrix_transform.hpp>

#include "hazel/renderer/render_command.h"
#include "hazel/renderer/shader.h"
#include "hazel/renderer/vertex_array.h"
#include "hzpch.h"

namespace hazel {

struct Renderer2DStorage {
  Ref<VertexArray> quadVertexArray;
  Ref<Shader>      textureShader;
  Ref<Texture2D>   whiteTexture;
};

static Renderer2DStorage* s_data;

void Renderer2D::Init() {
  s_data                  = new Renderer2DStorage();
  s_data->quadVertexArray = VertexArray::Create();

  float squareVertices[5 * 4] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  //
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  //
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  //
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  //
  };

  Ref<VertexBuffer> squareVB;
  squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
  squareVB->SetLayout({
      {ShaderDataType::Float3, "a_position"},
      {ShaderDataType::Float2, "a_texCoord"},
  });
  s_data->quadVertexArray->AddVertexBuffer(squareVB);

  uint32_t         squareIndices[6] = {0, 1, 2, 2, 3, 0};
  Ref<IndexBuffer> squareIB;
  squareIB = IndexBuffer::Create(squareIndices,
                                 sizeof(squareIndices) / sizeof(uint32_t));
  s_data->quadVertexArray->SetIndexBuffer(squareIB);

  s_data->whiteTexture      = Texture2D::Create(1, 1);
  uint32_t whiteTextureData = 0xffffffff;
  s_data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

  s_data->textureShader = Shader::Create("assets/shaders/texture.glsl");
  s_data->textureShader->Bind();
  s_data->textureShader->SetInt("u_texture", 0);
}

void Renderer2D::Shutdown() { delete s_data; }

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
  s_data->textureShader->Bind();
  s_data->textureShader->SetMat4("u_vp", camera.GetVP());
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
                          const glm::vec4& color) {
  DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          const glm::vec4& color) {
  s_data->textureShader->SetFloat4("u_color", color);
  s_data->whiteTexture->Bind();

  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

  s_data->textureShader->SetMat4("u_transform", transform);
  s_data->quadVertexArray->Bind();
  RenderCommand::DrawIndexed(s_data->quadVertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
                          const glm::vec4&      color,
                          const Ref<Texture2D>& texture) {
  DrawQuad({position.x, position.y, 0.0f}, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          const Ref<Texture2D>& texture) {
  s_data->textureShader->SetFloat4("u_color", glm::vec4(1.0f));
  texture->Bind();

  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  s_data->textureShader->SetMat4("u_transform", transform);

  s_data->quadVertexArray->Bind();
  RenderCommand::DrawIndexed(s_data->quadVertexArray);
}

}  // namespace hazel
