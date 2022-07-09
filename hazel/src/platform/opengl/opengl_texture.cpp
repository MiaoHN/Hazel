#include "opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "hazel/log.h"
#include "hzpch.h"

namespace hazel {

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : _path(path) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  HZ_CORE_ASSERT(data, "Failed to load image!");
  _width = width;
  _height = height;

  unsigned int internalFormat = 0, dataFormat = 0;
  if (channels == 4) {
    internalFormat = GL_RGBA8;
    dataFormat = GL_RGBA;
  } else if (channels == 3) {
    internalFormat = GL_RGB8;
    dataFormat = GL_RGB;
  }

  HZ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

  glCreateTextures(GL_TEXTURE_2D, 1, &_id);
  glTextureStorage2D(_id, 1, internalFormat, _width, _height);

  glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(_id, 0, 0, 0, _width, _height, dataFormat,
                      GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &_id); }

void OpenGLTexture2D::Bind(unsigned int slot) const {
  glBindTextureUnit(slot, _id);
}

}  // namespace hazel
