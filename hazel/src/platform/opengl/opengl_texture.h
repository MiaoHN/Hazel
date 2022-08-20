#pragma once

#include <glad/glad.h>

#include "hazel/renderer/texture.h"

namespace hazel {

class OpenGLTexture2D : public Texture2D {
 public:
  OpenGLTexture2D(uint32_t width, uint32_t height);
  OpenGLTexture2D(const std::string& path);
  ~OpenGLTexture2D();

  unsigned int GetWidth() const override { return width_; }
  unsigned int GetHeight() const override { return height_; }

  void SetData(void* data, uint32_t size) const override;

  void Bind(unsigned int slot = 0) const override;

 private:
  std::string  path_;
  unsigned int width_, height_;
  unsigned int id_;

  unsigned int internalFormat_, dataFormat_;
};

}  // namespace hazel
