#ifndef __EVENT_H__
#define __EVENT_H__

#include "hzpch.h"
#include "hazel/core.h"

namespace hazel {

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  AppTick,
  AppUpdate,
  AppRender,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MounseButtonReleased,
  MouseMoved,
  MouseScrolled
};

enum EventCategory {
  None = 0,
  EventCategoryApplication = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4),
};

class HAZEL_API Event {
  friend class EventDispatcher;

 public:
  virtual EventType GetEventType() const = 0;
  virtual const char* GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); }

  inline bool IsInCategory(EventCategory category) {
    return GetCategoryFlags() & category;
  }

 protected:
  bool _handled = false;
};

class EventDispatcher {
  template <typename T>
  using EventFn = std::function<bool(T&)>;

 public:
  EventDispatcher(Event& event) : _event(event) {}

  template <typename T>
  bool Dispatch(EventFn<T> func) {
    if (_event.GetEventType() == T::GetStaticType()) {
      _event._handled = func(*(T*)&_event);
      return true;
    }
    return false;
  }

 private:
  Event& _event;
};

}  // namespace hazel

inline std::ostream& operator<<(std::ostream& os, const hazel::Event& e) {
  return os << e.ToString();
}

#endif  // __EVENT_H__