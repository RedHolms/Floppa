#include <Floppa/Renderer.h>

#if defined(_FLOPPA_WIN32)
#include "Win32/OpenGL3/Renderer.h"
#endif

namespace Floppa {

   Renderer::~Renderer() {}

   DynamicAllocated<Renderer> Renderer::New(RendererImpl tp, Window* window) {
      DynamicAllocated<Renderer> rendererInterface = nullptr;

#ifdef _FLOPPA_OS_IMPL_NAME
      switch (tp) {
      case RendererImpl_OpenGL3:
         rendererInterface = new Impl::_FLOPPA_OS_IMPL_NAME::OpenGL3::Renderer(window);
         break;

      default: break;
      }
#endif

      return rendererInterface;
   }

}