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
  _height = width;
  _height = height;

  glCreateTextures(GL_TEXTURE_2D, 1, &_id);
  glTextureStorage2D(_id, 1, GL_RGB8, _height, _height);

  glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(_id, 0, 0, 0, _height, _height, GL_RGB, GL_UNSIGNED_BYTE,
                      data);

  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &_id); }

void OpenGLTexture2D::Bind(unsigned int slot) const {
  glBindTextureUnit(slot, _id);
}

}  // namespace hazel
