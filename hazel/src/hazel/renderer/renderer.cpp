#include "hazel/renderer/renderer.h"

#include "hazel/renderer/renderer_2d.h"
#include "hzpch.h"
#include "platform/opengl/opengl_shader.h"

namespace hazel {

Scope<Renderer::SceneData> Renderer::s_sceneData =
    CreateScope<Renderer::SceneData>();

void Renderer::Init() {
  HZ_PROFILE_FUNCTION();

  RenderCommand::Init();
  Renderer2D::Init();
}

void Renderer::Shutdown() {
  HZ_PROFILE_FUNCTION();

  Renderer2D::Shutdown();
}

void Renderer::BeginScene(OrthographicCamera& camera) {
  HZ_PROFILE_FUNCTION();

  s_sceneData->vp = camera.GetVP();
}

void Renderer::EndScene() { HZ_PROFILE_FUNCTION(); }

void Renderer::Submit(const Ref<Shader>&      shader,
                      const Ref<VertexArray>& vertexArray,
                      const glm::mat4&        transform) {
  HZ_PROFILE_FUNCTION();

  shader->Bind();
  shader->SetMat4("u_vp", s_sceneData->vp);
  shader->SetMat4("u_transform", transform);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
  HZ_PROFILE_FUNCTION();

  RenderCommand::SetViewport(0, 0, width, height);
}

}  // namespace hazel
