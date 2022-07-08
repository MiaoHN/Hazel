#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

#include "hazel/events/application_event.h"
#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"
#include "hazel/layer.h"

namespace hazel {

class HAZEL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnImGuiRender() override;

  void Begin();
  void End();

 private:
  float _time = 0;
};

}  // namespace hazel

#endif  // __IMGUI_LAYER_H__