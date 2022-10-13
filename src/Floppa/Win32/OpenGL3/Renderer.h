#pragma once
#include <Floppa/Base.h>

#include <Floppa/Renderer.h>

namespace Floppa {

   class Window;
   
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            class GLBuffer;
            struct Renderer_Data;

            class Renderer : public Floppa::Renderer {
               friend GLBuffer;

            public:
               Renderer(Window* window);
               ~Renderer();

            public:
               RendererImpl GetRendererImpl();

               void OnWindowResized();

               void Render();
               void SwapBuffers();

               DynamicAllocated<Floppa::VertexBuffer> CreateVertexBuffer();
               DynamicAllocated<Floppa::IndexBuffer> CreateIndexBuffer();

            private:
               void AttachDrawer(DynamicAllocated<Drawer> drawer);

               void SelectContext();

               void SetupPixelFormat();

               void CreateContext();
               void DestroyContext();
               void InitOpenGL();

               void CreateOpenGLObjects();
               void DestroyOpenGLObjects();

               void CheckShader(unsigned int desc, const char* name);
               void CheckProgram(unsigned int desc);

               void SetupRenderState();

            private:
               DynamicAllocated<Renderer_Data> m;
            };

         }
      }
   }
}