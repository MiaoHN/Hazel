#include "windows_window.h"

#include "hazel/core/log.h"
#include "hazel/events/application_event.h"
#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"
#include "hzpch.h"
#include "platform/opengl/opengl_context.h"

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
  data_.title = props.title;
  data_.width = props.width;
  data_.height = props.height;

  HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width,
               props.height);

  if (!s_GLFWInitialized) {
    // TODO: glfwTerminate on system shutdown
    int success = glfwInit();
    HZ_CORE_ASSERT(success, "Could not initialize GLFW!");

    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  window_ = glfwCreateWindow((int)props.width, (int)props.height,
                             data_.title.c_str(), nullptr, nullptr);

  context_ = CreateScope<OpenGLContext>(window_);
  context_->Init();

  glfwSetWindowUserPointer(window_, &data_);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      window_, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event);
      });
  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.eventCallback(event);
  });
  glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode,
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
  glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int character) {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    KeyTypedEvent event(character);
    data.eventCallback(event);
  });
  glfwSetMouseButtonCallback(
      window_, [](GLFWwindow* window, int button, int action, int mods) {
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
      window_, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.eventCallback(event);
      });
  glfwSetCursorPosCallback(
      window_, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.eventCallback(event);
      });
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(window_); }

void WindowsWindow::OnUpdate() {
  glfwPollEvents();
  context_->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  data_.vSync = enabled;
}

bool WindowsWindow::IsVSync() const { return data_.vSync; }

}  // namespace hazel
