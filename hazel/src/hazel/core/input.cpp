#include "hazel/core/input.h"

#include "hzpch.h"

#ifdef HZ_PLATFORM_WINDOWS
#include "platform/windows/windows_input.h"
#else
#include "platform/windows/windows_input.h"
#endif

namespace hazel {

Scope<Input> Input::s_instance = Input::Create();

Scope<Input> Input::Create() {
#ifdef HZ_PLATFORM_WINDOWS
  return CreateScope<WindowsInput>();
#else
  return CreateScope<WindowsInput>();
#endif
  // HZ_CORE_ASSERT(false, "Unknown platform!");
  // return nullptr;
}

}  // namespace hazel
