#include <Floppa/Engine.h>
#include <Floppa/Window.h>
#include <Floppa/Renderer.h>
#include <Floppa/Encoding.h>
#include <Floppa/Drawer.h>

static Floppa::Engine* Engine;
static Floppa::Drawer* TrinagleDrawer;

int main() {
   int exit_code = 0;

   try {
      Engine = new Floppa::Engine();

#if !defined(DEBUG) && !defined(_DEBUG)
      Engine->SetConsoleVisibility(false);
#endif

      Engine->GetWindow()->SetTitle(Floppa::TransformStringFromWideToUTF8(L"Я Русский!").c_str());

      Floppa::DrawVertex vertices[] = {
         { {  0.5f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
         { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
         { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
         { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
         { { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 1.0f } },
         { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
      };

      TrinagleDrawer = Engine->GetRenderer()->CreateDrawer<Floppa::Drawer>();
      TrinagleDrawer->AddVertices(vertices, _FLOPPA_COUNTOF(vertices));

      Engine->Start();

      exit_code = Engine->GetExitCode();
   
      deallocate(Engine);
   }
   catch (Floppa::BaseException& e) {
      printf("Unhandled exception: %s\n", e.GetInformation().c_str());
      exit_code = 50001;
   }
   catch (std::exception& e) {
      printf("Unhandled exception: %s\n", e.what());
      exit_code = 50001;
   }

   return exit_code;
}