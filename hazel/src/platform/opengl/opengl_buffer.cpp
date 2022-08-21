#include "platform/opengl/opengl_buffer.h"

#include <glad/glad.h>

#include "hzpch.h"

namespace hazel {

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size) {
  HZ_PROFILE_FUNCTION();

  glCreateBuffers(1, &id_);
  glBindBuffer(GL_ARRAY_BUFFER, id_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  HZ_PROFILE_FUNCTION();

  glDeleteBuffers(1, &id_);
}

void OpenGLVertexBuffer::Bind() const {
  HZ_PROFILE_FUNCTION();

  glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void OpenGLVertexBuffer::UnBind() const {
  HZ_PROFILE_FUNCTION();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
    : _count(count) {
  HZ_PROFILE_FUNCTION();

  glCreateBuffers(1, &id_);
  glBindBuffer(GL_ARRAY_BUFFER, id_);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  HZ_PROFILE_FUNCTION();

  glDeleteBuffers(1, &id_);
}

void OpenGLIndexBuffer::Bind() const {
  HZ_PROFILE_FUNCTION();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void OpenGLIndexBuffer::UnBind() const {
  HZ_PROFILE_FUNCTION();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace hazel
