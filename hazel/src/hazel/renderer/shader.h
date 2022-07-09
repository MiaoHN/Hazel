#ifndef __SHADER_H__
#define __SHADER_H__

#include <glm/glm.hpp>
#include <string>

namespace hazel {

class Shader {
 public:
  Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
  ~Shader();

  void Bind() const;
  void UnBind() const;

  void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

 private:
  unsigned int _id;
};

}  // namespace hazel

#endif  // __SHADER_H__