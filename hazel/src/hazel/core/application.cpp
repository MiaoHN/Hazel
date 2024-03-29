#include "hazel/core/application.h"

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "hazel/core/input.h"
#include "hazel/core/log.h"
#include "hazel/events/application_event.h"
#include "hazel/renderer/renderer.h"

namespace hazel {

Application* Application::s_instance = nullptr;

Application::Application() {
  HZ_PROFILE_FUNCTION();

  HZ_CORE_ASSERT(!s_instance, "Application already exists!");
  s_instance = this;

  window_ = Window::Create();
  window_->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

  Renderer::Init();

  imguiLayer_ = new ImGuiLayer();
  PushOverlay(imguiLayer_);
}

Application::~Application() {
  HZ_PROFILE_FUNCTION();

  Renderer::Shutdown();
}

void Application::OnEvent(Event& e) {
  HZ_PROFILE_FUNCTION();
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      HZ_BIND_EVENT_FN(Application::OnWindowClose));
  dispatcher.Dispatch<WindowResizeEvent>(
      HZ_BIND_EVENT_FN(Application::OnWindowResize));

  for (auto it = layerStack_.rbegin(); it != layerStack_.rend(); ++it) {
    (*it)->OnEvent(e);
    if (e.handled) {
      break;
    }
  }
}

void Application::PushLayer(Layer* layer) {
  HZ_PROFILE_FUNCTION();

  layerStack_.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer) {
  HZ_PROFILE_FUNCTION();

  layerStack_.PushOverlay(layer);
}

void Application::Run() {
  HZ_PROFILE_FUNCTION();

  while (running_) {
    HZ_PROFILE_SCOPE("Run Loop");
    auto     time  = static_cast<float>(glfwGetTime());
    Timestep ts    = time - _lastFrameTime;
    _lastFrameTime = time;

    if (!minimized_) {
      HZ_PROFILE_SCOPE("LayerStack OnUpdate");
      for (Layer* layer : layerStack_) {
        layer->OnUpdate(ts);
      }
    }

    imguiLayer_->Begin();
    {
      HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");
      for (Layer* layer : layerStack_) {
        layer->OnImGuiRender();
      }
    }
    imguiLayer_->End();

    window_->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
  HZ_PROFILE_FUNCTION();
  running_ = false;
  return true;
}
bool Application::OnWindowResize(WindowResizeEvent& e) {
  HZ_PROFILE_FUNCTION();
  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    minimized_ = true;
    return false;
  }
  minimized_ = false;
  Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

  return false;
}

}  // namespace hazel
