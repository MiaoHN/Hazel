#include "hazel/core/layer_stack.h"

#include "hzpch.h"

namespace hazel {

LayerStack::~LayerStack() {
  for (Layer* layer : layers_) {
    layer->OnDetach();
    delete layer;
  }
}

void LayerStack::PushLayer(Layer* layer) {
  layers_.emplace(layers_.begin() + _layerInsertIndex, layer);
  _layerInsertIndex++;
  layer->OnAttach();
}

void LayerStack::PushOverlay(Layer* overlay) {
  layers_.emplace_back(overlay);
  overlay->OnAttach();
}

void LayerStack::PopLayer(Layer* layer) {
  auto it =
      std::find(layers_.begin(), layers_.begin() + _layerInsertIndex, layer);
  if (it != layers_.begin() + _layerInsertIndex) {
    layer->OnDetach();
    layers_.erase(it);
    _layerInsertIndex--;
  }
}

void LayerStack::PopOverlay(Layer* overlay) {
  auto it =
      std::find(layers_.begin() + _layerInsertIndex, layers_.end(), overlay);
  if (it != layers_.end()) {
    overlay->OnDetach();
    layers_.erase(it);
  }
}

}  // namespace hazel
