#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include "hazel/core.h"

namespace hazel {

class Texture {
 public:
  virtual ~Texture() = default;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual void Bind(unsigned int slot = 0) const = 0;
};

class Texture2D : public Texture {
 public:
  static Ref<Texture2D> Create(const std::string& path);
};

}  // namespace hazel

#endif  // __TEXTURE_H__