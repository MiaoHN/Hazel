#include "platform/opengl/opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "hazel/core/log.h"
#include "hzpch.h"

namespace hazel {

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
    : width_(width), height_(height) {
  internalFormat_ = GL_RGBA8;
  dataFormat_     = GL_RGBA;

  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glTextureStorage2D(id_, 1, internalFormat_, width_, height_);

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path_(path) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  HZ_CORE_ASSERT(data, "Failed to load image!");
  width_  = width;
  height_ = height;

  unsigned int internalFormat = 0, dataFormat = 0;
  if (channels == 4) {
    internalFormat = GL_RGBA8;
    dataFormat     = GL_RGBA;
  } else if (channels == 3) {
    internalFormat = GL_RGB8;
    dataFormat     = GL_RGB;
  }

  internalFormat_ = internalFormat;
  dataFormat_     = dataFormat;

  HZ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glTextureStorage2D(id_, 1, internalFormat, width_, height_);

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, dataFormat,
                      GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &id_); }

void OpenGLTexture2D::SetData(void* data, uint32_t size) const {
  uint32_t bpp = dataFormat_ == GL_RGBA ? 4 : 3;
  HZ_CORE_ASSERT(size == width_ * height_ * bpp,
                 "Data must be entire texture!");
  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, dataFormat_,
                      GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(unsigned int slot) const {
  glBindTextureUnit(slot, id_);
}

}  // namespace hazel
