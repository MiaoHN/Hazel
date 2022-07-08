#ifndef __OPENGL_CONTEXT_H__
#define __OPENGL_CONTEXT_H__

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

#endif  // __OPENGL_CONTEXT_H__