#include "hazel/renderer/renderer.h"

#include "hzpch.h"

namespace hazel {

Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

void Renderer::BeginScene(OrthoGraphicCamera& camera) {
  s_sceneData->vp = camera.GetVP();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<VertexArray>& vertexArray,
                      const glm::mat4& transform) {
  shader->Bind();
  shader->UploadUniformMat4("u_vp", s_sceneData->vp);
  shader->UploadUniformMat4("u_transform", transform);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace hazel
