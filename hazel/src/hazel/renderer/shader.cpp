#include "hazel/renderer/shader.h"

#include "hazel/core/log.h"
#include "hazel/renderer/renderer.h"
#include "hzpch.h"
#include "platform/opengl/opengl_shader.h"

namespace hazel {

Ref<Shader> Shader::Create(const std::string& filepath) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false, "Renderer::API::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(filepath);
  }
  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<Shader> Shader::Create(const std::string& name,
                           const std::string& vertexSrc,
                           const std::string& fragmentSrc) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      HZ_CORE_ASSERT(false, "Renderer::API::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
  }
  HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
  HZ_CORE_ASSERT(!Exists(name), "Shader already exists!");
  shaders_[name] = shader;
}

void ShaderLibrary::Add(const Ref<Shader>& shader) {
  auto& name = shader->GetName();
  Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
  auto shader = Shader::Create(filepath);
  Add(shader);
  return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& name,
                                const std::string& filepath) {
  auto shader = Shader::Create(filepath);
  Add(name, shader);
  return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name) {
  HZ_CORE_ASSERT(Exists(name), "Shader not found!");
  return shaders_[name];
}

bool ShaderLibrary::Exists(const std::string& name) const {
  return shaders_.find(name) != shaders_.end();
}

}  // namespace hazel
