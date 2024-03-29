#pragma once

#include "hazel/core/core.h"
#include "hazel/events/event.h"
#include "hzpch.h"

namespace hazel {

struct WindowProps {
  std::string  title;
  unsigned int width;
  unsigned int height;

  WindowProps(const std::string& _title = "Hazel Engine",
              unsigned int _width = 1280, unsigned int _height = 720)
      : title(_title), width(_width), height(_height) {}
};

// Interface representing a desktop system based Window
class Window {
 public:
  using EventCallbackFn = std::function<void(Event&)>;

  virtual ~Window() {}

  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const  = 0;
  virtual unsigned int GetHeight() const = 0;

  // Window attributes
  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
  virtual void SetVSync(bool enabled)                            = 0;
  virtual bool IsVSync() const                                   = 0;

  virtual void* GetNativeWindow() const = 0;

  static Scope<Window> Create(const WindowProps& props = WindowProps());
};

}  // namespace hazel
