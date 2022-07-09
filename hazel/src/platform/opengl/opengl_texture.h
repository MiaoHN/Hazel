#ifndef __OPENGL_TEXTURE_H__
#define __OPENGL_TEXTURE_H__

#include "hazel/renderer/texture.h"

namespace hazel {

class OpenGLTexture2D : public Texture2D {
 public:
  OpenGLTexture2D(const std::string& path);
  ~OpenGLTexture2D();

  unsigned int GetWidth() const override { return _width; }
  unsigned int GetHeight() const override { return _height; }

  void Bind(unsigned int slot = 0) const override;

 private:
  std::string _path;
  unsigned int _width, _height;
  unsigned int _id;
};

}  // namespace hazel

#endif  // __OPENGL_TEXTURE_H__