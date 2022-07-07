#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"
#include "hazel/events/application_event.h"
#include "hazel/layer.h"
#include "platform/opengl/imgui_opengl_renderer.h"

namespace hazel {

class HAZEL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach();
  void OnDetach();
  void OnUpdate();
  void OnEvent(Event& event);

 private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
  bool OnMouseMovedEvent(MouseMovedEvent& e);
  bool OnMouseScrolledEvent(MouseScrolledEvent& e);
  bool OnKeyPressedEvent(KeyPressedEvent& e);
  bool OnKeyReleasedEvent(KeyReleasedEvent& e);
  bool OnKeyTypedEvent(KeyTypedEvent& e);
  bool OnWindowResizedEvent(WindowResizeEvent& e);

 private:
  float _time = 0;
};

}  // namespace hazel

#endif  // __IMGUI_LAYER_H__