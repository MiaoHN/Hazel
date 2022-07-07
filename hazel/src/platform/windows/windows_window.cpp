#include "windows_window.h"

#include "hazel/events/application_event.h"
#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"

namespace hazel {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
  HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

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

    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  _window = glfwCreateWindow((int)props.width, (int)props.height,
                             _data.title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, &_data);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      _window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event);
      });
  glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.eventCallback(event);
  });
  glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode,
                                 int action, int mods) {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action) {
      case GLFW_PRESS: {
        KeyPressedEvent event(key, 0);
        data.eventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        KeyReleasedEvent event(key);
        data.eventCallback(event);
        break;
      }
      case GLFW_REPEAT: {
        KeyPressedEvent event(key, 1);
        data.eventCallback(event);
        break;
      }
    }
  });
  glfwSetMouseButtonCallback(
      _window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.eventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.eventCallback(event);
            break;
          }
        }
      });
  glfwSetScrollCallback(
      _window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.eventCallback(event);
      });
  glfwSetCursorPosCallback(
      _window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.eventCallback(event);
      });
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
