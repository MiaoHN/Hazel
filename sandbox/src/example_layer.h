#pragma once

#include "hazel.h"

class ExampleLayer : public hazel::Layer {
 public:
  ExampleLayer();

  void OnUpdate(hazel::Timestep ts) override;

  void OnImGuiRender() override;

  void OnEvent(hazel::Event& event) override;

 private:
  hazel::ShaderLibrary           shaderLibrary_;
  hazel::Ref<hazel::Shader>      shader_;
  hazel::Ref<hazel::VertexArray> vertexArray_;

  hazel::Ref<hazel::Shader>      flatColorShader_;
  hazel::Ref<hazel::VertexArray> squareVA_;

  hazel::Ref<hazel::Texture2D> texture_, chernoLogoTexture_;

  hazel::OrthographicCameraController cameraController_;
  glm::vec3                           squareColor_ = {0.2f, 0.3f, 0.8f};
};