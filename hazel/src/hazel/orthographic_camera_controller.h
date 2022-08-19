#pragma once

#include "hazel/core/time_step.h"
#include "hazel/events//application_event.h"
#include "hazel/events/mouse_event.h"
#include "hazel/renderer/orthographic_camera.h"

namespace hazel {

class OrthographicCameraController {
 public:
  OrthographicCameraController(float aspectRatio, bool rotation = false);

  void onUpdate(Timestep ts);
  void onEvent(Event& e);

  OrthographicCamera& GetCamera() { return camera_; }
  const OrthographicCamera& GetCamera() const { return camera_; }

 private:
  bool onMouseScrolled(MouseScrolledEvent& e);
  bool onWindowResized(WindowResizeEvent& e);

 private:
  float aspectRatio_;
  float zoomLevel_ = 1.0f;
  OrthographicCamera camera_;

  bool rotation_;

  glm::vec3 cameraPosition_ = {0.0f, 0.0f, 0.0f};
  float cameraRotation_ = 0.0f;
  float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;
};

}  // namespace hazel