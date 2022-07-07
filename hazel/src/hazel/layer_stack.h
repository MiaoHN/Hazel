#ifndef __LAYER_STACK_H__
#define __LAYER_STACK_H__

#include <vector>

#include "hazel/core.h"
#include "hazel/layer.h"

namespace hazel {

class HAZEL_API LayerStack {
 public:
  LayerStack();
  ~LayerStack();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);
  void PopLayer(Layer* layer);
  void PopOverlay(Layer* overlay);

  std::vector<Layer*>::iterator begin() { return _layers.begin(); }
  std::vector<Layer*>::iterator end() { return _layers.end(); }

 private:
  std::vector<Layer*> _layers;
  std::vector<Layer*>::iterator _layerInsert;
};

}  // namespace hazel

#endif  // __LAYER_STACK_H__