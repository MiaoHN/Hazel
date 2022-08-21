#include "platform/opengl/opengl_vertex_array.h"

#include <glad/glad.h>

#include "hzpch.h"

namespace hazel {

static unsigned int

ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:
      return GL_FLOAT;
    case ShaderDataType::Float2:
      return GL_FLOAT;
    case ShaderDataType::Float3:
      return GL_FLOAT;
    case ShaderDataType::Float4:
      return GL_FLOAT;
    case ShaderDataType::Mat3:
      return GL_FLOAT;
    case ShaderDataType::Mat4:
      return GL_FLOAT;
    case ShaderDataType::Int:
      return GL_INT;
    case ShaderDataType::Int2:
      return GL_INT;
    case ShaderDataType::Int3:
      return GL_INT;
    case ShaderDataType::Int4:
      return GL_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    case ShaderDataType::None:
      break;
  }

  HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
  HZ_PROFILE_FUNCTION();

  glCreateVertexArrays(1, &id_);
}

OpenGLVertexArray::~OpenGLVertexArray() {
  HZ_PROFILE_FUNCTION();

  glDeleteVertexArrays(1, &id_);
}

void OpenGLVertexArray::Bind() const {
  HZ_PROFILE_FUNCTION();

  glBindVertexArray(id_);
}

void OpenGLVertexArray::UnBind() const {
  HZ_PROFILE_FUNCTION();

  glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
  HZ_PROFILE_FUNCTION();

  HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                 "Vertex Buffer has no layout!");

  glBindVertexArray(id_);
  vertexBuffer->Bind();

  unsigned int index  = 0;
  const auto&  layout = vertexBuffer->GetLayout();
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

void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
  HZ_PROFILE_FUNCTION();

  glBindVertexArray(id_);
  indexBuffer->Bind();

  _indexBuffer = indexBuffer;
}

}  // namespace hazel
