#include "application.h"

#include "hazel/events/application_event.h"
#include "log.h"

namespace hazel {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  WindowResizeEvent e(1280, 720);
  if (e.IsInCategory(EventCategoryApplication)) {
    HZ_CLIENT_TRACE(e.ToString());
  }
  if (e.IsInCategory(EventCategoryInput)) {
    HZ_CLIENT_TRACE(e.ToString());
  }
  while (true) {
  }
}

}  // namespace hazel
