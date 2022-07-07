#include "windows_window.h"

namespace hazel {

static bool s_GLFWInitialized = false;

Window* Window::Create(const WindowProps& props) {
  return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }

WindowsWindow::~WindowsWindow() { Shutdown(); }

void WindowsWindow::Init(const WindowProps& props) {
  _data.title = props.title;
  _data.width = props.width;
  _data.height = props.height;

  HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width,
               props.height);

  if (!s_GLFWInitialized) {
    // TODO: glfwTerminate on system shutdown
    int success = glfwInit();
    HZ_CORE_ASSERT(success, "Could not initialize GLFW!");

    s_GLFWInitialized = true;
  }

  _window = glfwCreateWindow((int)props.width, (int)props.height,
                             _data.title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, &_data);
  SetVSync(true);
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(_window); }

void WindowsWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(_window);
}

void WindowsWindow::SetVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  _data.vSync = enabled;
}

bool WindowsWindow::IsVSync() const { return _data.vSync; }

}  // namespace hazel
