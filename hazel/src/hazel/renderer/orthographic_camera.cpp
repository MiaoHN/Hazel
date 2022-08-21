#include "hazel/renderer/orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "hzpch.h"

namespace hazel {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top)
    : projection_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      view_(1.0f) {
  HZ_PROFILE_FUNCTION();

  vp_ = projection_ * view_;
}

void OrthographicCamera::RecalculateView() {
  HZ_PROFILE_FUNCTION();

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position_) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

  view_ = glm::inverse(transform);
  vp_   = projection_ * view_;
}
void OrthographicCamera::SetProjection(float left, float right, float bottom,
                                       float top) {
  HZ_PROFILE_FUNCTION();

  projection_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  vp_         = projection_ * view_;
}

}  // namespace hazel
