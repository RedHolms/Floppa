#include "Window.h"

#include <assert.h>
#include <string.h>

#include <windows.h>

#include <Floppa/Encoding.h>

static bool Floppa_Win32WindowClassCreated = false;

uintptr_t __stdcall Floppa_Win32WindowProcedure(void* winHandle, unsigned message, uintptr_t wParam, uintptr_t lParam) {
   Floppa::Impl::Win32::Window* windowImplInstance = reinterpret_cast<Floppa::Impl::Win32::Window*>(GetWindowLongPtrW(reinterpret_cast<HWND>(winHandle), GWLP_USERDATA));
   if (windowImplInstance)
      return windowImplInstance->WindowProcedure(message, wParam, lParam);
   return DefWindowProcW(reinterpret_cast<HWND>(winHandle), message, wParam, lParam);
}

static void Floppa_Win32CreateWindowClass() {
   WNDCLASSW wndClass {0};
   wndClass.style = 0;
   wndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(&Floppa_Win32WindowProcedure);
   wndClass.cbClsExtra = 0;
   wndClass.cbWndExtra = 0;
   wndClass.hInstance = reinterpret_cast<HINSTANCE>(Floppa::NonClient::InstanceHandle);
   wndClass.hIcon = NULL;
   wndClass.hCursor = NULL;
   wndClass.hbrBackground = NULL;
   wndClass.lpszMenuName = NULL;
   wndClass.lpszClassName = Floppa::Impl::Win32::WindowClassName;

   ATOM atom = RegisterClassW(&wndClass);

   // ToDo: Make normal error handling
   assert(atom && "Failed to create window class");

   Floppa_Win32WindowClassCreated = true;
}

namespace Floppa {
   namespace Impl {
      namespace Win32 {

         struct Window_Data {
            HWND winHandle;
            MSG lastMessage;
            bool wantExit;
            uintptr_t windowClosingCode;
            WindowEventHandler coreEventHandler;
         };

         Window::Window(const char* title, int sx, int sy) {
            m = new Window_Data;

            memset(&m->lastMessage, 0, sizeof(MSG));
            m->wantExit = false;
            m->windowClosingCode = 0;

            if (!Floppa_Win32WindowClassCreated)
               Floppa_Win32CreateWindowClass();

            m->winHandle = CreateWindowW(
               WindowClassName,
               Floppa::TransformStringFromUTF8ToWide(title).c_str(),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               sx, sy,
               NULL,
               NULL,
               reinterpret_cast<HINSTANCE>(Floppa::NonClient::InstanceHandle),
               NULL
            );

            // ToDo: Make normal error handling
            assert(m->winHandle && "Failed to create window");

            SetWindowLongPtrW(m->winHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
         }

         Window::~Window() {
            if (m->winHandle) {
               DestroyWindow(m->winHandle);
            }

            deallocate(m);
         }

         std::string Window::GetTitle() {
            if (!m->winHandle) _FLOPPA_THROW_EXCEPTION(WindowNotOpenException, "Window::GetTitle()");

            int length = GetWindowTextLengthW(m->winHandle) + 1;
            wchar_t* buff = new wchar_t[length];

            GetWindowTextW(m->winHandle, buff, length);
            buff[length - 1] = 0;

            std::string result = Floppa::TransformStringFromWideToUTF8(buff);

            delete[] buff;

            return result;
         }

         void Window::SetTitle(const char* title) {
            if (!m->winHandle) _FLOPPA_THROW_EXCEPTION(WindowNotOpenException, "Window::SetTitle()");

            SetWindowTextW(m->winHandle, Floppa::TransformStringFromUTF8ToWide(title).c_str());
         }

         bool Window::IsVisible() {
            if (!m->winHandle) _FLOPPA_THROW_EXCEPTION(WindowNotOpenException, "Window::IsVisible()");

            return IsWindowVisible(m->winHandle);
         }

         void Window::SetVisibility(bool vis) {
            if (!m->winHandle) _FLOPPA_THROW_EXCEPTION(WindowNotOpenException, "Window::SetVisibility()");

            ShowWindow(m->winHandle, vis ? SW_SHOW : SW_HIDE);
            UpdateWindow(m->winHandle);
         }

         bool Window::IsOpen() {
            return m->winHandle != NULL;
         }

         bool Window::IsWantExit() {
            return m->wantExit;
         }

         int Window::GetClosingCode() {
            return static_cast<int>(m->windowClosingCode);
         }

         WindowSystemHandle Window::GetSystemHandle() {
            WindowSystemHandle handle {0};
            handle.win32Handle = m->winHandle;
            return handle;
         }

         void Window::Update() {
            memset(&m->lastMessage, 0, sizeof(MSG));

            while (PeekMessageW(&m->lastMessage, m->winHandle, 0, 0, PM_REMOVE)) {
               TranslateMessage(&m->lastMessage);
               DispatchMessageW(&m->lastMessage);
            }
         }

         void Window::SetCoreEventHandler(WindowEventHandler const& handler) {
            m->coreEventHandler = handler;
         }

         uintptr_t Window::WindowProcedure(unsigned message, uintptr_t wParam, uintptr_t lParam) {
            switch (message) {
            case WM_DESTROY:
               m->winHandle = NULL;
               m->wantExit = true;
               m->windowClosingCode = 0;
               break;

            case WM_SIZE: {
               if (m->coreEventHandler) m->coreEventHandler(WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));
            } break;

            default: return DefWindowProcW(m->winHandle, message, wParam, lParam);
            }

            return 0;
         }

      }
   }
}