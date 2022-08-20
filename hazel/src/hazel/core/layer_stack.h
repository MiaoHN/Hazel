#ifndef __LAYER_STACK_H__
#define __LAYER_STACK_H__

#include <vector>

#include "core.h"
#include "layer.h"

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
  unsigned int _layerInsertIndex = 0;
};

}  // namespace hazel

#endif  // __LAYER_STACK_H__