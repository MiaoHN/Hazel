#ifndef __OPENGL_BUFFER_H__
#define __OPENGL_BUFFER_H__

#include "hazel/renderer/buffer.h"

namespace hazel {

class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* vertices, unsigned int size);
  ~OpenGLVertexBuffer();

  void Bind() const override;
  void UnBind() const override;

 private:
  unsigned int _id;
};

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
  virtual ~OpenGLIndexBuffer();

  void Bind() const override;
  void UnBind() const override;

  virtual unsigned int GetCount() const { return _count; }

 private:
  unsigned int _id;
  unsigned int _count;
};

}  // namespace hazel

#endif  // __OPENGL_BUFFER_H__