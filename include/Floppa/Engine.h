#pragma once
#include "Base.h"

#include <string>
#include <vector>

#include "Exceptions.h"

namespace Floppa {

   class WindowEvent;
   class Renderer;
   class Window;
   class Drawer;

   using EngineRendererPrefer = int;
   enum EngineRendererPrefer_ {
      EngineRendererPrefer_OpenGL, // OpenGL with any version
      EngineRendererPrefer_OpenGL3, // Try OpenGL 3.0 or newer, if not accept - throw error
      EngineRendererPrefer_DirectX, // DirectX with any version, will lock to Win32 only
      EngineRendererPrefer_DirectX9, // Try DirectX 9.0 or newer, if not accept - throw error, will lock to Win32 only
      EngineRendererPrefer_DirectX11, // Try DirectX 11.0 or newer, if not accept - throw error, will lock to Win32 only
      EngineRendererPrefer_OpenGL_DirectX, // Try EngineRendererPrefer_OpenGL on X11, EngineRendererPrefer_DirectX on Win32
      EngineRendererPrefer_OpenGL3_DirectX, // Try EngineRendererPrefer_OpenGL3 on X11, EngineRendererPrefer_DirectX on Win32
      EngineRendererPrefer_OpenGL_DirectX9, // Try EngineRendererPrefer_OpenGL on X11, EngineRendererPrefer_DirectX9 on Win32
      EngineRendererPrefer_OpenGL_DirectX11, // Try EngineRendererPrefer_OpenGL on X11, EngineRendererPrefer_DirectX11 on Win32
      EngineRendererPrefer_OpenGL3_DirectX9, // Try EngineRendererPrefer_OpenGL3 on X11, EngineRendererPrefer_DirectX9 on Win32
      EngineRendererPrefer_OpenGL3_DirectX11, // Try EngineRendererPrefer_OpenGL3 on X11, EngineRendererPrefer_DirectX11 on Win32
   };

   struct EngineConfig {
      const char* windowName;
      int windowSizeX, windowSizeY;
      EngineRendererPrefer rendererPrefer;
      bool consoleVisibility;
      DynamicAllocated<Window> customWindow;
      DynamicAllocated<Renderer> customRenderer;
   };

   extern EngineConfig DefaultEngineConfig;

   class Engine {
   public:
      _FLOPPA_API Engine();
      _FLOPPA_API Engine(EngineConfig& cfg);
      _FLOPPA_API ~Engine();
   
   public:
      _FLOPPA_API void Start();

      _FLOPPA_API void SetConsoleVisibility(bool v);

      _FLOPPA_API Window* GetWindow() const;
      _FLOPPA_API Renderer* GetRenderer() const;

      _FLOPPA_API int GetExitCode();

   private:
      _FLOPPA_PRIVATE_API void CoreEventHandler(WindowEvent& e);

      _FLOPPA_PRIVATE_API void StartGameLoop();
      _FLOPPA_PRIVATE_API void Loop();

      _FLOPPA_PRIVATE_API void Update();
      _FLOPPA_PRIVATE_API void Draw();
      _FLOPPA_PRIVATE_API void Render();
   
   private:
      DynamicAllocated<Window> m_window;
      DynamicAllocated<Renderer> m_renderer;
      int m_exitCode;
   };

}

namespace Floppa {

   class NoAvailableWindowImplimentationException : public BaseException {
   public:
      NoAvailableWindowImplimentationException(std::string throwedFunc, const char* throwedFile, int throwedLine)
         : BaseException("Can't create window because no avaible implimentation exists (check your OS)", throwedFunc, throwedFile, throwedLine) {}

      OSType GetTargetOS() { return TargetOS; }
   };

   class NoAvailableRendererImplimentationException : public BaseException {
   public:
      NoAvailableRendererImplimentationException(std::vector<int> tryied, std::string throwedFunc, const char* throwedFile, int throwedLine)
         : m_tryied(tryied),
         BaseException("Can't create window because no avaible implimentation exists (check renderer prefer given to engine and your OS)", throwedFunc, throwedFile, throwedLine) {}

      std::vector<int> GetTryied() { return m_tryied; }

   private:
      std::vector<int> m_tryied;
   };

}