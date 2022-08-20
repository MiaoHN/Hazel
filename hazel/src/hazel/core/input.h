#ifndef __INPUT_H__
#define __INPUT_H__

#include "core.h"
#include "hzpch.h"

namespace hazel {

class HAZEL_API Input {
 protected:
  Input() = default;

 public:
  Input(const Input&) = delete;
  Input& operator=(const Input&) = delete;

  inline static bool IsKeyPressed(int keyCode) {
    return s_instance->IsKeyPressedImpl(keyCode);
  }
  inline static bool IsMouseButtonPressed(int button) {
    return s_instance->IsMouseButtonPressedImpl(button);
  }

  inline static std::pair<float, float> GetMousePosition() {
    return s_instance->GetMousePositionImpl();
  }
  inline static float GetMouseX() { return s_instance->GetMouseXImpl(); }
  inline static float GetMouseY() { return s_instance->GetMouseYImpl(); }

 protected:
  virtual bool IsKeyPressedImpl(int keyCode) = 0;
  virtual bool IsMouseButtonPressedImpl(int button) = 0;
  virtual std::pair<float, float> GetMousePositionImpl() = 0;
  virtual float GetMouseXImpl() = 0;
  virtual float GetMouseYImpl() = 0;

 private:
  static Scope<Input> s_instance;
};

}  // namespace hazel

#endif  // __INPUT_H__