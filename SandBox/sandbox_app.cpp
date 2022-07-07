#include <hazel.h>

class ExampleLayer : public hazel::Layer {
 public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override { HZ_INFO("ExampleLayer::Update"); }

  void OnEvent(hazel::Event& event) override {
    HZ_TRACE("{0}", event.ToString());
  }
};

class Sandbox : public hazel::Application {
 public:
  Sandbox() {
    PushLayer(new ExampleLayer());
    PushOverlay(new hazel::ImGuiLayer());
  }
  ~Sandbox() {}

 private:
};

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }