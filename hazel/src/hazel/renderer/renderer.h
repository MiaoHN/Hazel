#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace hazel {

enum class RendererAPI {
  None = 0,
  OpenGL = 1,
};

class Renderer {
 public:
  inline static RendererAPI GetAPI() { return s_rendererAPI; }

 private:
  static RendererAPI s_rendererAPI;
};

}  // namespace hazel

#endif  // __RENDERER_H__