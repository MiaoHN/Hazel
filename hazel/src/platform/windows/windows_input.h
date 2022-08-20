#ifndef __WINDOWS_INPUT_H__
#define __WINDOWS_INPUT_H__

#include "hazel/core/input.h"
#include "hzpch.h"

namespace hazel {

class WindowsInput : public Input {
 protected:
  bool IsKeyPressedImpl(int keyCode) override;
  bool IsMouseButtonPressedImpl(int button) override;
  std::pair<float, float> GetMousePositionImpl() override;
  float GetMouseXImpl() override;
  float GetMouseYImpl() override;
};

}  // namespace hazel

#endif  // __WINDOWS_INPUT_H__