#ifndef __LAYER_H__
#define __LAYER_H__

#include "hazel/core.h"
#include "hazel/core/time_step.h"
#include "hazel/events/event.h"

namespace hazel {

class HAZEL_API Layer {
 public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(Timestep ts) {}
  virtual void OnImGuiRender() {}
  virtual void OnEvent(Event& event) {}

  inline const std::string& GetName() const { return _debugName; }

 protected:
  std::string _debugName;
};

}  // namespace hazel

#endif  // __LAYER_H__