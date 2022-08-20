#pragma once

#include "hazel/renderer/vertex_array.h"

namespace hazel {

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  ~OpenGLVertexArray();

  void Bind() const override;
  void UnBind() const override;

  void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
  void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

  const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override {
    return _vertexBuffers;
  }
  const Ref<IndexBuffer>& GetIndexBuffer() const override {
    return _indexBuffer;
  }

 private:
  unsigned int id_;
  unsigned int _vertexBufferIndexOffset = 0;

  std::vector<Ref<VertexBuffer>> _vertexBuffers;
  Ref<IndexBuffer>               _indexBuffer;
};

}  // namespace hazel
