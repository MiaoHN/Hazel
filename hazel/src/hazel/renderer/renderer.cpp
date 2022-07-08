#include "hazel/renderer/renderer.h"

#include "hzpch.h"

namespace hazel {

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace hazel
