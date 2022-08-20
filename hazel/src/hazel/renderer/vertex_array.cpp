#include "hazel/renderer/vertex_array.h"

#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_vertex_array.h"

namespace hazel {

Ref<VertexArray> VertexArray::Create() {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false,
                     "RendererAPI::API::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLVertexArray>();
  }
  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace hazel
