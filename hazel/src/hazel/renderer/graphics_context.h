#ifndef __GRAPHICS_CONTEXT_H__
#define __GRAPHICS_CONTEXT_H__

namespace hazel {

class GraphicsContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};

}  // namespace hazel

#endif  // __GRAPHICS_CONTEXT_H__