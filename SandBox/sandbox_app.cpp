#include <hazel.h>

class Sandbox : public hazel::Application {
 public:
  Sandbox() {}
  ~Sandbox() {}

 private:
};

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }