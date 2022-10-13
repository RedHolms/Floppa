#include <Floppa/Engine.h>

#include <Floppa/Window.h>
#include <Floppa/Renderer.h>
#include <Floppa/Drawer.h>

#ifdef _FLOPPA_WIN32
#include <Windows.h>
#endif

namespace Floppa {
   namespace NonClient {
      void* InstanceHandle = nullptr;
   }
}

// Init Floppa::NonClient::InstanceHandle on windows if shared lib
#if defined(_FLOPPA_WIN32) && defined(_FLOPPA_SHARED)
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, BOOL bSysCall) {
   if (fdwReason == DLL_PROCESS_ATTACH) {
      Floppa::NonClient::InstanceHandle = reinterpret_cast<void*>(hinstDLL);
      DisableThreadLibraryCalls(hinstDLL);
   }
   return TRUE;
}
#endif

namespace Floppa {

   EngineConfig DefaultEngineConfig = {
      "Floppa Engine Window",
      1280, 720,
      EngineRendererPrefer_OpenGL,
#if defined(DEBUG) || defined(_DEBUG)
      true,
#else
      false,
#endif
      nullptr, nullptr
   };

   Engine::Engine() : Engine(DefaultEngineConfig) {}

   Engine::Engine(EngineConfig& cfg) {
      m_exitCode = 0;

      if (cfg.customWindow)
         m_window = std::move(cfg.customWindow);
      else
         m_window = Window::New(cfg.windowName, cfg.windowSizeX, cfg.windowSizeY);


      if (cfg.customRenderer)
         m_renderer = std::move(cfg.customRenderer);
      else {
         std::vector<RendererImpl> tryiedRendererImpls;

         switch (cfg.rendererPrefer) {
         case EngineRendererPrefer_OpenGL:
         case EngineRendererPrefer_OpenGL3:
            tryiedRendererImpls.push_back(RendererImpl_OpenGL3);
            m_renderer = Renderer::New(RendererImpl_OpenGL3, m_window);
            break;

            case EngineRendererPrefer_DirectX:
            case EngineRendererPrefer_DirectX9:
            case EngineRendererPrefer_DirectX11:
            case EngineRendererPrefer_OpenGL_DirectX:
            case EngineRendererPrefer_OpenGL3_DirectX:
            case EngineRendererPrefer_OpenGL_DirectX9:
            case EngineRendererPrefer_OpenGL_DirectX11:
            case EngineRendererPrefer_OpenGL3_DirectX9:
            case EngineRendererPrefer_OpenGL3_DirectX11:
         default:
            break;
         }

         // make sure renderer was created, otherwise - throw exception
         if (!m_renderer)
            _FLOPPA_THROW_EXCEPTION_EX(NoAvailableRendererImplimentationException, "Engine::Engine()", tryiedRendererImpls);
      }

      m_window->SetCoreEventHandler([this](auto& e) { this->CoreEventHandler(e); });
      SetConsoleVisibility(cfg.consoleVisibility);
   }

   Engine::~Engine() {
      deallocate(m_renderer);
      deallocate(m_window);
   }

   void Engine::Start() {
      m_exitCode = 0;

      m_window->SetVisibility(true);
      m_renderer->OnWindowResized();
      
      StartGameLoop();
   }

   void Engine::SetConsoleVisibility(bool v) {
#ifdef _FLOPPA_WIN32
      ShowWindow(GetConsoleWindow(), v ? SW_SHOW : SW_HIDE);
#else
      (void)v;
#endif
   }

   DynamicAllocated<Window> const& Engine::GetWindow() const {
      return m_window;
   }

   DynamicAllocated<Renderer> const& Engine::GetRenderer() const {
      return m_renderer;
   }

   int Engine::GetExitCode() {
      return m_exitCode;
   }

   void Engine::CoreEventHandler(WindowEvent& e) {
      switch (e.GetEventType()) {
      case WindowEventType_WindowResized:
         m_renderer->OnWindowResized();
         break;
      }
   }

   void Engine::StartGameLoop() {
      while (m_window->IsOpen())
         Loop();
      m_exitCode = m_window->GetClosingCode();
   }

   void Engine::Loop() {
      Update();
      Draw();
      Render();
   }

   void Engine::Update() {
      m_window->Update();
   }

   void Engine::Draw() {
      /* do draw */
   }

   void Engine::Render() {
      m_renderer->Render();
      m_renderer->SwapBuffers();
   }

}