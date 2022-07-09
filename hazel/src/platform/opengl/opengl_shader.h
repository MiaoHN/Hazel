#ifndef __OPENGL_SHADER_H__
#define __OPENGL_SHADER_H__

#include <glm/glm.hpp>

#include "hazel/renderer/shader.h"
#include "hzpch.h"

namespace hazel {

class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& filepath);
  OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
  ~OpenGLShader();

  void Bind() const override;
  void UnBind() const override;

  void UploadUniformInt(const std::string& name, int value);

  void UploadUniformFloat(const std::string& name, float value);
  void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
  void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
  void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

  void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
  void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

 private:
  std::string ReadFile(const std::string& filepath);
  std::unordered_map<unsigned int, std::string> PreProcess(
      const std::string& source);
  void Compile(
      const std::unordered_map<unsigned int, std::string>& shaderSources);

 private:
  unsigned int _id;
};

}  // namespace hazel

#endif  // __OPENGL_SHADER_H__