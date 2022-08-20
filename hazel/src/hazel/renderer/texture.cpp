#include "hazel/renderer/texture.h"

#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_texture.h"

namespace hazel {

Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLTexture2D>(width, height);
  }

  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<Texture2D> Texture2D::Create(const std::string& path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLTexture2D>(path);
  }

  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace hazel
