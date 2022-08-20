#include "sandbox_2d.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
  checkerboardTexture_ =
      hazel::Texture2D::Create("assets/textures/checker_board.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(hazel::Timestep ts) {
  // Update
  cameraController_.onUpdate(ts);

  // Render
  hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
  hazel::RenderCommand::Clear();

  hazel::Renderer2D::BeginScene(cameraController_.GetCamera());
  hazel::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f},
                              {0.8f, 0.2f, 0.3f, 1.0f});
  hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f},
                              {0.2f, 0.3f, 0.8f, 1.0f});
  hazel::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f},
                              checkerboardTexture_);
  hazel::Renderer2D::EndScene();

  hazel::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor_));
  ImGui::End();
}

void Sandbox2D::OnEvent(hazel::Event& e) { cameraController_.onEvent(e); }
