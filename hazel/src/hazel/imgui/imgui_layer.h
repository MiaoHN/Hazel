#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

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
  float _time = 0;
};

}  // namespace hazel

#endif  // __IMGUI_LAYER_H__