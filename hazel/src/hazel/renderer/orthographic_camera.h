#pragma once

#include <glm/glm.hpp>

namespace hazel {

class OrthographicCamera {
 public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void SetProjection(float left, float right, float bottom, float top);

  const glm::vec3& GetPosition() const { return position_; }
  void             SetPosition(const glm::vec3& position) {
                position_ = position;
                RecalculateView();
  }

  float GetRotation() const { return rotation_; }
  void  SetRotation(float rotation) {
     rotation_ = rotation;
     RecalculateView();
  }

  const glm::mat4& GetProjection() const { return projection_; }
  const glm::mat4& GetView() const { return view_; }
  const glm::mat4& GetVP() const { return vp_; }

 private:
  void RecalculateView();

 private:
  glm::mat4 projection_;
  glm::mat4 view_;
  glm::mat4 vp_;

  glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
  float     rotation_ = 0.0f;
};

}  // namespace hazel
