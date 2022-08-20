#pragma once

#include <glm/glm.hpp>

#include "hazel/renderer/shader.h"
#include "hzpch.h"

namespace hazel {

class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& filepath);
  OpenGLShader(const std::string& name, const std::string& vertexSrc,
               const std::string& fragmentSrc);
  ~OpenGLShader();

  void Bind() const override;
  void UnBind() const override;

  const std::string& GetName() const override { return name_; }

  void SetInt(const std::string& name, int value) override;
  void SetFloat3(const std::string& name, const glm::vec3& value) override;
  void SetFloat4(const std::string& name, const glm::vec4& value) override;
  void SetMat4(const std::string& name, const glm::mat4& value) override;

  void UploadUniformInt(const std::string& name, int value) const;

  void UploadUniformFloat(const std::string& name, float value) const;
  void UploadUniformFloat2(const std::string& name,
                           const glm::vec2&   value) const;
  void UploadUniformFloat3(const std::string& name,
                           const glm::vec3&   value) const;
  void UploadUniformFloat4(const std::string& name,
                           const glm::vec4&   value) const;

  void UploadUniformMat3(const std::string& name,
                         const glm::mat3&   matrix) const;
  void UploadUniformMat4(const std::string& name,
                         const glm::mat4&   matrix) const;

 private:
  std::string ReadFile(const std::string& filepath);
  static std::unordered_map<unsigned int, std::string> PreProcess(
      const std::string& source);
  void Compile(
      const std::unordered_map<unsigned int, std::string>& shaderSources);

 private:
  unsigned int id_;
  std::string  name_;
};

}  // namespace hazel
