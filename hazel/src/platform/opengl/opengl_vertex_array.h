#ifndef __OPENGL_VERTEX_ARRAY_H__
#define __OPENGL_VERTEX_ARRAY_H__

#include "hazel/renderer/vertex_array.h"

namespace hazel {

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  ~OpenGLVertexArray();

  void Bind() const override;
  void UnBind() const override;

  void AddVertexBuffer(
      const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

  const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()
      const override {
    return _vertexBuffers;
  }
  const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {
    return _indexBuffer;
  }

 private:
  unsigned int _id;
  unsigned int _vertexBufferIndexOffset = 0;
  std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
  std::shared_ptr<IndexBuffer> _indexBuffer;
};

}  // namespace hazel

#endif  // __OPENGL_VERTEX_ARRAY_H__