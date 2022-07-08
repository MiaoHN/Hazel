#ifndef __RENDERER_API_H__
#define __RENDERER_API_H__

#include <glm/glm.hpp>

#include "hazel/renderer/vertex_array.h"

namespace hazel {

class RendererAPI {
 public:
  enum class API {
    None = 0,
    OpenGL = 1,
  };

 public:
  virtual void SetClearColor(const glm::vec4& color) = 0;
  virtual void Clear() = 0;

  virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexAray) = 0;

  inline static API GetAPI() { return s_API; }

 private:
  static API s_API;
};

}  // namespace hazel

#endif  // __RENDERER_API_H__