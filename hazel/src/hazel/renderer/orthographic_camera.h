#ifndef __ORTHOGRAPHIC_CAMERA_H__
#define __ORTHOGRAPHIC_CAMERA_H__

#include <glm/glm.hpp>

namespace hazel {

class OrthoGraphicCamera {
 public:
  OrthoGraphicCamera(float left, float right, float bottom, float top);

  const glm::vec3& GetPosition() const { return _position; }
  void SetPosition(const glm::vec3& position) {
    _position = position;
    RecalculateView();
  }

  float GetRotation() const { return _rotation; }
  void SetRotation(float rotation) {
    _rotation = rotation;
    RecalculateView();
  }

  const glm::mat4& GetProjection() const { return _projection; }
  const glm::mat4& GetView() const { return _view; }
  const glm::mat4& GetVP() const { return _vp; }

 private:
  void RecalculateView();

 private:
  glm::mat4 _projection;
  glm::mat4 _view;
  glm::mat4 _vp;

  glm::vec3 _position = {0.0f, 0.0f, 0.0f};
  float _rotation = 0.0f;
};

}  // namespace hazel

#endif  // __ORTHOGRAPHIC_CAMERA_H__