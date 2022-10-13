#pragma once
#include <Floppa/Base.h>

#include <stdint.h>

#include <Floppa/Window.h>

uintptr_t __stdcall Floppa_Win32WindowProcedure(void*, unsigned, uintptr_t, uintptr_t);

namespace Floppa {
   namespace Impl {
      namespace Win32 {

         constexpr const wchar_t* WindowClassName = L"_FLOPPA_ENGINE_WINDOW_CLASS_";

         struct Window_Data;

         class Window : public Floppa::Window {
            friend uintptr_t __stdcall ::Floppa_Win32WindowProcedure(void*, unsigned, uintptr_t, uintptr_t);

         public:
            Window(const char* title, int sx, int sy);
            ~Window();

         public:
            std::string GetTitle();
            void SetTitle(const char* title);
            bool IsVisible();
            void SetVisibility(bool vis);
            bool IsOpen();
            bool IsWantExit();
            int GetClosingCode();
            WindowSystemHandle GetSystemHandle();

         private:
            void Update();
            void SetCoreEventHandler(WindowEventHandler const& handler);

            uintptr_t WindowProcedure(unsigned message, uintptr_t wParam, uintptr_t lParam);

         private:
            DynamicAllocated<Window_Data> m;
         };

      }
   }
}