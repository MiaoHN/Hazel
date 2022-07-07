#ifndef __MOUSE_EVENT_H__
#define __MOUSE_EVENT_H__

#include <sstream>

#include "event.h"

namespace hazel {

class HAZEL_API MouseMovedEvent : public Event {
 public:
  MouseMovedEvent(float x, float y) : _mouseX(x), _mouseY(y) {}

  inline float GetX() const { return _mouseX; }
  inline float GetY() const { return _mouseY; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
    return ss.str();
  }

  static EventType GetStaticType() { return EventType::MouseMoved; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "MouseMoved"; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryMouse | EventCategoryInput;
  }

 private:
  float _mouseX, _mouseY;
};

class HAZEL_API MouseScrolledEvent : public Event {
 public:
  MouseScrolledEvent(float xOffset, float yOffset)
      : _xOffset(xOffset), _yOffset(yOffset) {}

  inline float GetXOffset() const { return _xOffset; }
  inline float GetYOffset() const { return _yOffset; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
    return ss.str();
  }

  static EventType GetStaticType() { return EventType::MouseScrolled; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "MouseScrolled"; }
  virtual int GetCategoryFlags() const override {
    return EventCategoryMouse | EventCategoryInput;
  }

 private:
  float _xOffset, _yOffset;
};

class HAZEL_API MouseButtonEvent : public Event {
 public:
  inline int GetMouseButton() const { return _button; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryMouseButton | EventCategoryInput;
  }

 protected:
  MouseButtonEvent(int button) : _button(button) {}

  int _button;
};

class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << _button;
    return ss.str();
  }

  static EventType GetStaticType() { return EventType::MouseButtonPressed; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "MouseButtonPressed"; }
};

class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << _button;
    return ss.str();
  }

  static EventType GetStaticType() { return EventType::MouseButtonReleased; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "MouseButtonReleased"; }
};

}  // namespace hazel

#endif  // __MOUSE_EVENT_H__