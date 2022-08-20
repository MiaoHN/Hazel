#pragma once

#include "hazel/events/event.h"
#include "hzpch.h"

namespace hazel {

class KeyEvent : public Event {
 public:
  inline int GetKeyCode() const { return _keyCode; }

  int GetCategoryFlags() const override {
    return EventCategoryKeyboard | EventCategoryInput;
  }

 protected:
  KeyEvent(int keyCode) : _keyCode(keyCode) {}

 protected:
  int _keyCode;
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(int keyCode, int repeatCount)
      : KeyEvent(keyCode), _repeatCount(repeatCount) {}

  inline int GetRepeatCount() const { return _repeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << _keyCode << " (" << _repeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)

 private:
  int _repeatCount;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << _keyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
 public:
  KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyTyped: " << _keyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyTyped)
};

}  // namespace hazel
