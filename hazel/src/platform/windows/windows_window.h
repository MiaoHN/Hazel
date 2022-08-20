#ifndef __WINDOWS_WINDOW_H__
#define __WINDOWS_WINDOW_H__

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "hazel/core/window.h"
#include "hazel/renderer/graphics_context.h"

namespace hazel {

class WindowsWindow : public Window {
 public:
  WindowsWindow(const WindowProps& props);
  ~WindowsWindow();

  void OnUpdate() override;

  inline unsigned int GetWidth() const override { return data_.width; }
  inline unsigned int GetHeight() const override { return data_.height; }

  // Windows attributes
  inline void SetEventCallback(const EventCallbackFn& callback) override {
    data_.eventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  inline void* GetNativeWindow() const override { return window_; }

 private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();

 private:
  GLFWwindow* window_;
  Scope<GraphicsContext> context_;

  struct WindowData {
    std::string title;
    unsigned int width, height;
    bool vSync;

    EventCallbackFn eventCallback;
  };

  WindowData data_;
};

}  // namespace hazel

#endif  // __WINDOWS_WINDOW_H__