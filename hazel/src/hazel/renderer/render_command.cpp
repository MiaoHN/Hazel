#include "hazel/renderer/render_command.h"

#include "hzpch.h"
#include "platform/opengl/opengl_renderer_api.h"

namespace hazel {

Scope<RendererAPI> RenderCommand::s_renderAPI =
    CreateScope<OpenGLRendererAPI>();

}  // namespace hazel
