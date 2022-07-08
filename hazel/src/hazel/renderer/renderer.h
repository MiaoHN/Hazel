#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "hazel/renderer/render_command.h"
#include "hazel/renderer/renderer_api.h"

namespace hazel {

class Renderer {
 public:
  static void BeginScene();
  static void EndScene();

  static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};

}  // namespace hazel

#endif  // __RENDERER_H__