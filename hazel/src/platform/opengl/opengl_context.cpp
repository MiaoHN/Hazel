#include "platform/opengl/opengl_context.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "hazel/core/log.h"
#include "hzpch.h"

namespace hazel {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : _windowHandle(windowHandle) {
  HZ_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(_windowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

  HZ_CORE_INFO("OpenGL Info");
  HZ_CORE_INFO("  Vendor:   {0}", glGetString(GL_VENDOR));
  HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  HZ_CORE_INFO("  Version:  {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(_windowHandle); }

}  // namespace hazel
