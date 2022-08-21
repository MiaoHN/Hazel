#include "hazel/core/window.h"

#ifdef HZ_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#else
#include "platform/windows/windows_window.h"
#endif

namespace hazel {

Scope<Window> Window::Create(const WindowProps& props) {
#ifdef HZ_PLATFORM_WINDOWS
  return CreateScope<WindowsWindow>(props);
#else
  return CreateScope<WindowsWindow>(props);
#endif
  // HZ_CORE_ASSERT(false, "Unknown platform!");
  // return nullptr;
}

}  // namespace hazel