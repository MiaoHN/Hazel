#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <unordered_map>

#include "../core.h"

namespace hazel {

class Shader {
 public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  virtual const std::string& GetName() const = 0;

  static Ref<Shader> Create(const std::string& filepath);
  static Ref<Shader> Create(const std::string& name,
                            const std::string& vertexSrc,
                            const std::string& fragmentSrc);
};

class ShaderLibrary {
 public:
  void Add(const std::string& name, const Ref<Shader>& shader);
  void Add(const Ref<Shader>& shader);
  Ref<Shader> Load(const std::string& filepath);
  Ref<Shader> Load(const std::string& name, const std::string& filepath);

  Ref<Shader> Get(const std::string& name);

  bool Exists(const std::string& name) const;

 private:
  std::unordered_map<std::string, Ref<Shader>> shaders_;
};

}  // namespace hazel

#endif  // __SHADER_H__