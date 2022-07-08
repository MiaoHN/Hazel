#include "hazel/renderer/render_command.h"

#include "hzpch.h"
#include "platform/opengl/opengl_renderer_api.h"

namespace hazel {

RendererAPI* RenderCommand::s_renderAPI = new OpenGLRendererAPI;

}  // namespace hazel
