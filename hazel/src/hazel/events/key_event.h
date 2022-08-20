#ifndef __KEY_EVENT_H__
#define __KEY_EVENT_H__

#include "hazel/events/event.h"
#include "hzpch.h"

namespace hazel {

class HAZEL_API KeyEvent : public Event {
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

class HAZEL_API KeyPressedEvent : public KeyEvent {
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

class HAZEL_API KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << _keyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

class HAZEL_API KeyTypedEvent : public KeyEvent {
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

#endif  // __KEY_EVENT_H__