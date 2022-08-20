#pragma once

#include "hazel/renderer/graphics_context.h"

struct GLFWwindow;

namespace hazel {

class OpenGLContext : public GraphicsContext {
 public:
  OpenGLContext(GLFWwindow* windowHandle);

  void Init() override;
  void SwapBuffers() override;

 private:
  GLFWwindow* _windowHandle;
};

}  // namespace hazel
