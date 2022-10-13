#include <Floppa/Window.h>

#if defined(_FLOPPA_WIN32)
#include "Win32/Window.h"
#endif

namespace Floppa {

   Window::~Window() {}

   DynamicAllocated<Window> Window::New(const char* title, int sx, int sy) {
      DynamicAllocated<Window> windowInterface = nullptr;

#ifdef _FLOPPA_OS_IMPL_NAME
      windowInterface = new Impl::_FLOPPA_OS_IMPL_NAME::Window(title, sx, sy);
#endif

      return windowInterface;
   }

}