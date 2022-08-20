#ifndef __APPLICATION_EVENT_H__
#define __APPLICATION_EVENT_H__

#include "hazel/core/core.h"
#include "hazel/events/event.h"
#include "hzpch.h"

namespace hazel {

class HAZEL_API WindowResizeEvent : public Event {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : _width(width), _height(height) {}

  inline unsigned int GetWidth() const { return _width; }
  inline unsigned int GetHeight() const { return _height; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << _width << ", " << _height;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)

  int GetCategoryFlags() const override { return EventCategoryApplication; }

 private:
  unsigned int _width, _height;
};

class HAZEL_API WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() {}

  EVENT_CLASS_TYPE(WindowClose)

  int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class HAZEL_API AppTickEvent : public Event {
 public:
  AppTickEvent() {}

  EVENT_CLASS_TYPE(AppTick)

  int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class HAZEL_API AppUpdateEvent : public Event {
 public:
  AppUpdateEvent() {}

  EVENT_CLASS_TYPE(AppUpdate)

  int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class HAZEL_API AppRenderEvent : public Event {
 public:
  AppRenderEvent() {}

  EVENT_CLASS_TYPE(AppRender)

  int GetCategoryFlags() const override { return EventCategoryApplication; }
};

}  // namespace hazel

#endif  // __APPLICATION_EVENT_H__