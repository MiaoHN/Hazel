#include "hazel/renderer/shader.h"

#include "hazel/log.h"
#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_shader.h"

namespace hazel {

Shader* Shader::Create(const std::string& vertexSrc,
                       const std::string& fragmentSrc) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false, "Renderer::API::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return new OpenGLShader(vertexSrc, fragmentSrc);
  }
  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace hazel
