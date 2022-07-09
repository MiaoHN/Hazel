#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "hazel/renderer/orthographic_camera.h"
#include "hazel/renderer/render_command.h"
#include "hazel/renderer/renderer_api.h"
#include "hazel/renderer/shader.h"

namespace hazel {

class Renderer {
 public:
  static void BeginScene(OrthoGraphicCamera& camera);
  static void EndScene();

  static void Submit(const std::shared_ptr<Shader>& shader,
                     const std::shared_ptr<VertexArray>& vertexArray);
  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

 private:
  struct SceneData {
    glm::mat4 vp;
  };

  static SceneData* s_sceneData;
};

}  // namespace hazel

#endif  // __RENDERER_H__