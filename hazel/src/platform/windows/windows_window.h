#ifndef __WINDOWS_WINDOW_H__
#define __WINDOWS_WINDOW_H__

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "hazel/window.h"

namespace hazel {

class WindowsWindow : public Window {
 public:
  WindowsWindow(const WindowProps& props);
  ~WindowsWindow();

  void OnUpdate() override;

  inline unsigned int GetWidth() const override { return _data.width; }
  inline unsigned int GetHeight() const override { return _data.height; }

  // Windows attributes
  inline void SetEventCallback(const EventCallbackFn& callback) override {
    _data.eventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

 private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();

 private:
  GLFWwindow* _window;

  struct WindowData {
    std::string title;
    unsigned int width, height;
    bool vSync;

    EventCallbackFn eventCallback;
  };

  WindowData _data;
};

}  // namespace hazel

#endif  // __WINDOWS_WINDOW_H__