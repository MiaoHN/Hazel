#pragma once

#include "hazel/core/core.h"

namespace hazel {

class GraphicsContext {
 public:
  virtual void Init()        = 0;
  virtual void SwapBuffers() = 0;

  static Scope<GraphicsContext> Create(void* window);
};

}  // namespace hazel
