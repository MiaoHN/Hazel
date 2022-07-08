#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

namespace hazel {

class Shader {
 public:
  Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
  ~Shader();

  void Bind() const;
  void UnBind() const;

 private:
  unsigned int _id;
};

}  // namespace hazel

#endif  // __SHADER_H__