#pragma once

#include "hazel.h"

class Sandbox2D : public hazel::Layer {
 public:
  Sandbox2D();
  virtual ~Sandbox2D() = default;

  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(hazel::Timestep ts) override;
  void OnImGuiRender() override;
  void OnEvent(hazel::Event& e) override;

 private:
  hazel::OrthographicCameraController cameraController_;

  // Temp
  hazel::Ref<hazel::VertexArray> squareVA_;
  hazel::Ref<hazel::Shader> flatColorShader_;

  hazel::Ref<hazel::Texture2D> checkerboardTexture_;

  glm::vec4 squareColor_ = {0.2f, 0.3f, 0.8f, 1.0f};
};