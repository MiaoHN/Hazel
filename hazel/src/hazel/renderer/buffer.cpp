#include "hazel/renderer/buffer.h"

#include "hazel/log.h"
#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_buffer.h"

namespace hazel {

VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::None:
      HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return new OpenGLVertexBuffer(vertices, size);
  }

  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::None:
      HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return new OpenGLIndexBuffer(indices, size);
  }

  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace hazel
