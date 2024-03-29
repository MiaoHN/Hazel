#pragma once

#include <glm/glm.hpp>

#include "hazel/renderer/orthographic_camera.h"
#include "hazel/renderer/render_command.h"
#include "hazel/renderer/renderer_api.h"
#include "hazel/renderer/shader.h"

namespace hazel {

class Renderer {
 public:
  static void Init();
  static void Shutdown();
  static void OnWindowResize(uint32_t width, uint32_t height);

  static void BeginScene(OrthographicCamera& camera);
  static void EndScene();

  static void Submit(const Ref<Shader>&      shader,
                     const Ref<VertexArray>& vertexArray,
                     const glm::mat4&        transform = glm::mat4(1.0f));

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

 private:
  struct SceneData {
    glm::mat4 vp;
  };

  static Scope<SceneData> s_sceneData;
};

}  // namespace hazel
