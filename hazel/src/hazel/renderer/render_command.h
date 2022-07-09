#ifndef __RENDER_COMMAND_H__
#define __RENDER_COMMAND_H__

#include "hazel/renderer/renderer_api.h"

namespace hazel {

class RenderCommand {
 public:
  inline static void Init() { s_renderAPI->Init(); }

  inline static void SetClearColor(const glm::vec4& color) {
    s_renderAPI->SetClearColor(color);
  }

  inline static void Clear() { s_renderAPI->Clear(); }

  inline static void DrawIndexed(
      const std::shared_ptr<VertexArray>& vertexArray) {
    s_renderAPI->DrawIndexed(vertexArray);
  }

 private:
  static RendererAPI* s_renderAPI;
};

}  // namespace hazel

#endif  // __RENDER_COMMAND_H__