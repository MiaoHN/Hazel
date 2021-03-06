#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

namespace hazel {

class Shader {
 public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  static Shader* Create(const std::string& filepath);
  static Shader* Create(const std::string& vertexSrc,
                        const std::string& fragmentSrc);
};

}  // namespace hazel

#endif  // __SHADER_H__