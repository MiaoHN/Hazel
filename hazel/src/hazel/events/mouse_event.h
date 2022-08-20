#pragma once

#include "event.h"
#include "hzpch.h"

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

  EVENT_CLASS_TYPE(MouseMoved)

  int GetCategoryFlags() const override {
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

  EVENT_CLASS_TYPE(MouseScrolled)

  int GetCategoryFlags() const override {
    return EventCategoryMouse | EventCategoryInput;
  }

 private:
  float _xOffset, _yOffset;
};

class HAZEL_API MouseButtonEvent : public Event {
 public:
  inline int GetMouseButton() const { return _button; }

  int GetCategoryFlags() const override {
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

  EVENT_CLASS_TYPE(MouseButtonPressed)
};

class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << _button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonReleased)
};

}  // namespace hazel
