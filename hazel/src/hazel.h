#ifndef __HAZEL_H__
#define __HAZEL_H__

// For use by Hazel applications

#include "hazel/application.h"
#include "hazel/core/time_step.h"
#include "hazel/imgui/imgui_layer.h"
#include "hazel/input.h"
#include "hazel/key_code.h"
#include "hazel/layer.h"
#include "hazel/log.h"
#include "hazel/mouse_button_code.h"
#include "hazel/orthographic_camera_controller.h"

// ----- Renderer
#include "hazel/renderer/buffer.h"
#include "hazel/renderer/orthographic_camera.h"
#include "hazel/renderer/render_command.h"
#include "hazel/renderer/renderer.h"
#include "hazel/renderer/shader.h"
#include "hazel/renderer/texture.h"
#include "hazel/renderer/vertex_array.h"
// -----

// ----- Entry Point
#include "hazel/entry_point.h"
// -----

#endif  // __HAZEL_H__