#include "orthographic_camera_controller.h"

#include "hazel/core/input.h"
#include "hazel/core/key_code.h"
#include "hzpch.h"

namespace hazel {

OrthographicCameraController::OrthographicCameraController(float aspectRatio,
                                                           bool rotation)
    : aspectRatio_(aspectRatio),
      camera_(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_,
              -zoomLevel_, zoomLevel_),
      rotation_(rotation) {}

void OrthographicCameraController::onUpdate(Timestep ts) {
  if (Input::IsKeyPressed((HZ_KEY_A))) {
    cameraPosition_.x -=
        std::cos(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
    cameraPosition_.y -=
        std::sin(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
  } else if (Input::IsKeyPressed((HZ_KEY_D))) {
    cameraPosition_.x +=
        std::cos(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
    cameraPosition_.y +=
        std::sin(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
  }

  if (Input::IsKeyPressed((HZ_KEY_W))) {
    cameraPosition_.x +=
        -std::sin(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
    cameraPosition_.y +=
        std::cos(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
  } else if (Input::IsKeyPressed((HZ_KEY_S))) {
    cameraPosition_.x -=
        -std::sin(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
    cameraPosition_.y -=
        std::cos(glm::radians(cameraRotation_)) * cameraTranslationSpeed * ts;
  }

  if (rotation_) {
    if (Input::IsKeyPressed(HZ_KEY_Q)) {
      cameraRotation_ += cameraRotationSpeed * ts;
    }
    if (Input::IsKeyPressed(HZ_KEY_E)) {
      cameraRotation_ -= cameraRotationSpeed * ts;
    }

    if (cameraRotation_ > 180.0f) {
      cameraRotation_ -= 360.0f;
    } else if (cameraRotation_ <= 180.0f) {
      cameraRotation_ += 360.0f;
    }

    camera_.SetRotation(cameraRotation_);
  }
  camera_.SetPosition(cameraPosition_);
  cameraTranslationSpeed = zoomLevel_;
}

void OrthographicCameraController::onEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(
      HZ_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(
      HZ_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
}

bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) {
  zoomLevel_ -= e.GetYOffset() * 0.25f;
  zoomLevel_ = std::max(zoomLevel_, 0.25f);
  camera_.SetProjection(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_,
                        -zoomLevel_, zoomLevel_);
  return false;
}

bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e) {
  aspectRatio_ = (float)e.GetWidth() / (float)e.GetHeight();
  camera_.SetProjection(-aspectRatio_ * zoomLevel_, aspectRatio_ * zoomLevel_,
                        -zoomLevel_, zoomLevel_);
  return false;
}

}  // namespace hazel