#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "core.h"
#include "events/event.h"

namespace hazel {

class HAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();
};

// To be defined in client
Application* CreateApplication();

}  // namespace hazel

#endif  // __APPLICATION_H__