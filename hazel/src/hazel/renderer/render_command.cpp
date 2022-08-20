#include "hazel/renderer/render_command.h"

#include "hzpch.h"

namespace hazel {

Scope<RendererAPI> RenderCommand::s_renderAPI = RendererAPI::Create();

}  // namespace hazel
