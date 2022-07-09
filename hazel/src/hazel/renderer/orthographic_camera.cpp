#include "hazel/renderer/orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "hzpch.h"

namespace hazel {

OrthoGraphicCamera::OrthoGraphicCamera(float left, float right, float bottom,
                                       float top)
    : _projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      _view(1.0f) {
  _vp = _projection * _view;
}

void OrthoGraphicCamera::RecalculateView() {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), _position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

  _view = glm::inverse(transform);
  _vp = _projection * _view;
}

}  // namespace hazel
