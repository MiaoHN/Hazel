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

  static EventType GetStaticType() { return EventType::WindowResize; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "WindowResize"; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryApplication;
  }

 private:
  unsigned int _width, _height;
};

class HAZEL_API WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() {}

  static EventType GetStaticType() { return EventType::WindowClose; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "WindowClose"; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryApplication;
  }
};

class HAZEL_API AppTickEvent : public Event {
 public:
  AppTickEvent() {}

  static EventType GetStaticType() { return EventType::AppTick; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "AppTick"; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryApplication;
  }
};

class HAZEL_API AppUpdateEvent : public Event {
 public:
  AppUpdateEvent() {}

  static EventType GetStaticType() { return EventType::AppUpdate; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "AppUpdate"; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryApplication;
  }
};

class HAZEL_API AppRenderEvent : public Event {
 public:
  AppRenderEvent() {}

  static EventType GetStaticType() { return EventType::AppRender; }
  virtual EventType GetEventType() const override { return GetStaticType(); }
  virtual const char* GetName() const override { return "AppRender"; }

  virtual int GetCategoryFlags() const override {
    return EventCategoryApplication;
  }
};

}  // namespace hazel

#endif  // __APPLICATION_EVENT_H__