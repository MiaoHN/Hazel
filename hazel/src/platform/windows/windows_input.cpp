#include "platform/windows/windows_input.h"

#include <GLFW/glfw3.h>

#include "hazel/core/application.h"
#include "hzpch.h"

namespace hazel {

Scope<Input> Input::s_instance = CreateScope<WindowsInput>();

bool WindowsInput::IsKeyPressedImpl(int keyCode) {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetKey(window, keyCode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl() {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  return {(float)xPos, (float)yPos};
}

float WindowsInput::GetMouseXImpl() {
  auto pos = GetMousePositionImpl();
  return std::get<0>(pos);
}

float WindowsInput::GetMouseYImpl() {
  auto pos = GetMousePositionImpl();
  return std::get<1>(pos);
}

}  // namespace hazel
