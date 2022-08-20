#include "platform/opengl/opengl_vertex_array.h"

#include <glad/glad.h>

#include "hzpch.h"

namespace hazel {

static unsigned int

ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
    case hazel::ShaderDataType::Float:
      return GL_FLOAT;
    case hazel::ShaderDataType::Float2:
      return GL_FLOAT;
    case hazel::ShaderDataType::Float3:
      return GL_FLOAT;
    case hazel::ShaderDataType::Float4:
      return GL_FLOAT;
    case hazel::ShaderDataType::Mat3:
      return GL_FLOAT;
    case hazel::ShaderDataType::Mat4:
      return GL_FLOAT;
    case hazel::ShaderDataType::Int:
      return GL_INT;
    case hazel::ShaderDataType::Int2:
      return GL_INT;
    case hazel::ShaderDataType::Int3:
      return GL_INT;
    case hazel::ShaderDataType::Int4:
      return GL_INT;
    case hazel::ShaderDataType::Bool:
      return GL_BOOL;
    case ShaderDataType::None:
      break;
  }

  HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

OpenGLVertexArray::OpenGLVertexArray() { glCreateVertexArrays(1, &_id); }

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &_id); }

void OpenGLVertexArray::Bind() const { glBindVertexArray(_id); }

void OpenGLVertexArray::UnBind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(
    const std::shared_ptr<VertexBuffer>& vertexBuffer) {
  HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                 "Vertex Buffer has no layout!");

  glBindVertexArray(_id);
  vertexBuffer->Bind();

  unsigned int index = 0;
  const auto& layout = vertexBuffer->GetLayout();
  for (const auto& element : layout) {
    glEnableVertexAttribArray(_vertexBufferIndexOffset);
    glVertexAttribPointer(_vertexBufferIndexOffset, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride(), (const void*)element.offset);
    _vertexBufferIndexOffset++;
  }
  _vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(
    const std::shared_ptr<IndexBuffer>& indexBuffer) {
  glBindVertexArray(_id);
  indexBuffer->Bind();

  _indexBuffer = indexBuffer;
}

}  // namespace hazel
