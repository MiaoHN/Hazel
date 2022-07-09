#include "hazel/renderer/texture.h"

#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_texture.h"

namespace hazel {

Ref<Texture2D> Texture2D::Create(const std::string& path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(path);
  }

  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace hazel
