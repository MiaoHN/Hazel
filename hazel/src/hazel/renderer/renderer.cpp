#include "hazel/renderer/renderer.h"

#include "hzpch.h"

namespace hazel {

Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

void Renderer::BeginScene(OrthoGraphicCamera& camera) {
  s_sceneData->vp = camera.GetVP();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<VertexArray>& vertexArray) {
  shader->Bind();
  shader->UploadUniformMat4("u_vp", s_sceneData->vp);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace hazel
