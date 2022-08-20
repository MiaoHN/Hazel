#pragma once

#include "hazel/renderer/buffer.h"

namespace hazel {

class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* vertices, unsigned int size);
  ~OpenGLVertexBuffer();

  void Bind() const override;
  void UnBind() const override;

  const BufferLayout& GetLayout() const override { return _layout; }
  void SetLayout(const BufferLayout& layout) override { _layout = layout; }

 private:
  unsigned int id_;
  BufferLayout _layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
  virtual ~OpenGLIndexBuffer();

  void Bind() const override;
  void UnBind() const override;

  virtual unsigned int GetCount() const { return _count; }

 private:
  unsigned int id_;
  unsigned int _count;
};

}  // namespace hazel
