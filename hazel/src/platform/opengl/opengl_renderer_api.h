#ifndef __OPENGL_RENDERER_API_H__
#define __OPENGL_RENDERER_API_H__

#include "hazel/renderer/renderer_api.h"
#include "hazel/renderer/vertex_array.h"

namespace hazel {

class OpenGLRendererAPI : public RendererAPI {
 public:
  void Init() override;

  void SetClearColor(const glm::vec4& color) override;
  void Clear() override;

  void DrawIndexed(const std::shared_ptr<VertexArray>& vertexAray) override;
};

}  // namespace hazel

#endif  // __OPENGL_RENDERER_API_H__