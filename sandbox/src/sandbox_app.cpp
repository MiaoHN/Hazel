#include <hazel.h>
#include <hazel/core/entry_point.h>

#include "example_layer.h"
#include "sandbox_2d.h"

class Sandbox : public hazel::Application {
 public:
  Sandbox() { PushLayer(new Sandbox2D()); }
  ~Sandbox() {}

 private:
};

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }