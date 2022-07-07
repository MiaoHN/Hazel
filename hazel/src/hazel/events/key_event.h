#ifndef __KEY_EVENT_H__
#define __KEY_EVENT_H__

#include "hzpch.h"
#include "hazel/events/event.h"

namespace hazel {

class HAZEL_API KeyEvent : public Event {
 public:
  inline int GetKeyCode() const { return _keyCode; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryKeyboard | EventCategoryInput;
  }

 protected:
  KeyEvent(int keyCode) : _keyCode(keyCode) {}

 private:
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

  static EventType GetStaticType() { return EventType::KeyPressed; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "KeyPressed"; }

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

  static EventType GetStaticType() { return EventType::KeyReleased; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "KeyReleased"; }
};

}  // namespace hazel

#endif  // __KEY_EVENT_H__