#pragma once

#include "hazel/core/log.h"

namespace hazel {

enum class ShaderDataType {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool,
};

static unsigned int ShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:
      return 4;
    case ShaderDataType::Float2:
      return 4 * 2;
    case ShaderDataType::Float3:
      return 4 * 3;
    case ShaderDataType::Float4:
      return 4 * 4;
    case ShaderDataType::Mat3:
      return 4 * 3 * 3;
    case ShaderDataType::Mat4:
      return 4 * 4 * 4;
    case ShaderDataType::Int:
      return 4;
    case ShaderDataType::Int2:
      return 4 * 2;
    case ShaderDataType::Int3:
      return 4 * 3;
    case ShaderDataType::Int4:
      return 4 * 4;
    case ShaderDataType::Bool:
      return 1;
  }

  HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

struct BufferElement {
  std::string    name;
  ShaderDataType type;
  unsigned int   size;
  size_t         offset;
  bool           normalized;

  BufferElement() = default;

  BufferElement(ShaderDataType _type, const std::string& _name,
                bool _normalized = false)
      : name(_name),
        type(_type),
        size(ShaderDataTypeSize(_type)),
        offset(0),
        normalized(_normalized) {}

  unsigned int GetComponentCount() const {
    switch (type) {
      case ShaderDataType::Float:
        return 1;
      case ShaderDataType::Float2:
        return 2;
      case ShaderDataType::Float3:
        return 3;
      case ShaderDataType::Float4:
        return 4;
      case ShaderDataType::Mat3:
        return 3 * 3;
      case ShaderDataType::Mat4:
        return 4 * 4;
      case ShaderDataType::Int:
        return 1;
      case ShaderDataType::Int2:
        return 2;
      case ShaderDataType::Int3:
        return 3;
      case ShaderDataType::Int4:
        return 4;
      case ShaderDataType::Bool:
        return 1;
    }
    HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }
};

class BufferLayout {
 public:
  BufferLayout() {}

  BufferLayout(const std::initializer_list<BufferElement>& elements)
      : _elements(elements) {
    CalculateOffsetsAndStride();
  }

  inline unsigned int                      GetStride() const { return _stride; }
  inline const std::vector<BufferElement>& GetElements() const {
    return _elements;
  }

  std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
  std::vector<BufferElement>::iterator end() { return _elements.end(); }
  std::vector<BufferElement>::const_iterator begin() const {
    return _elements.begin();
  }
  std::vector<BufferElement>::const_iterator end() const {
    return _elements.end();
  }

 private:
  void CalculateOffsetsAndStride() {
    size_t offset = 0;
    _stride       = 0;
    for (auto& element : _elements) {
      element.offset = offset;
      offset += element.size;
      _stride += element.size;
    }
  }

 private:
  std::vector<BufferElement> _elements;
  unsigned int               _stride = 0;
};

class VertexBuffer {
 public:
  virtual ~VertexBuffer() {}

  virtual void Bind() const   = 0;
  virtual void UnBind() const = 0;

  virtual const BufferLayout& GetLayout() const                     = 0;
  virtual void                SetLayout(const BufferLayout& layout) = 0;

  static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
};

class IndexBuffer {
 public:
  virtual ~IndexBuffer() {}

  virtual void Bind() const   = 0;
  virtual void UnBind() const = 0;

  virtual unsigned int GetCount() const = 0;

  static Ref<IndexBuffer> Create(unsigned int* indices, unsigned size);
};

}  // namespace hazel
