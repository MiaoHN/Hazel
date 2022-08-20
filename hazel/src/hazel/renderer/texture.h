#pragma once

#include <string>

#include "hazel/core/core.h"

namespace hazel {

class Texture {
 public:
  virtual ~Texture() = default;

  virtual unsigned int GetWidth() const  = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual void SetData(void* data, uint32_t size) const = 0;

  virtual void Bind(unsigned int slot = 0) const = 0;
};

class Texture2D : public Texture {
 public:
  static Ref<Texture2D> Create(uint32_t width, uint32_t height);
  static Ref<Texture2D> Create(const std::string& path);
};

}  // namespace hazel
