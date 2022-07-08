#include "hazel/renderer/vertex_array.h"

#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_vertex_array.h"

namespace hazel {

VertexArray* VertexArray::Create() {
  switch (Renderer::GetAPI()) {
    case RendererAPI::None:
      HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return new OpenGLVertexArray();
  }
  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace hazel
