#pragma once

#include "hazel/core/layer.h"
#include "hazel/events/application_event.h"
#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"

namespace hazel {

class ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;

  void Begin();
  void End();

 private:
  float _time = 0;
};

}  // namespace hazel
