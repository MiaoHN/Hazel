#ifndef __HAZEL_H__
#define __HAZEL_H__

// For use by Hazel applications

#include "hazel/core/application.h"
#include "hazel/core/input.h"
#include "hazel/core/key_code.h"
#include "hazel/core/layer.h"
#include "hazel/core/log.h"
#include "hazel/core/mouse_button_code.h"
#include "hazel/core/time_step.h"
#include "hazel/imgui/imgui_layer.h"
#include "hazel/renderer/orthographic_camera_controller.h"

// ----- Renderer
#include "hazel/renderer/buffer.h"
#include "hazel/renderer/orthographic_camera.h"
#include "hazel/renderer/render_command.h"
#include "hazel/renderer/renderer.h"
#include "hazel/renderer/renderer_2d.h"
#include "hazel/renderer/shader.h"
#include "hazel/renderer/texture.h"
#include "hazel/renderer/vertex_array.h"
// -----

#endif  // __HAZEL_H__