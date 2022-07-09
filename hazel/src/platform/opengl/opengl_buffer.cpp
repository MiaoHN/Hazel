#include "platform/opengl/opengl_buffer.h"

#include <glad/glad.h>

#include "hzpch.h"

namespace hazel {

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size) {
  glCreateBuffers(1, &_id);
  glBindBuffer(GL_ARRAY_BUFFER, _id);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &_id); }

void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }

void OpenGLVertexBuffer::UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
    : _count(count) {
  glCreateBuffers(1, &_id);
  glBindBuffer(GL_ARRAY_BUFFER, _id);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &_id); }

void OpenGLIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void OpenGLIndexBuffer::UnBind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace hazel
