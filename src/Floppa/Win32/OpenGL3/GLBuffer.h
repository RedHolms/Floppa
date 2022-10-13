#pragma once
#include <Floppa/Base.h>

#include <Floppa/Renderer.h>

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            class Renderer;

            class GLBuffer {
               friend Renderer;

            public:
               GLBuffer(Renderer* renderer, unsigned int target);
               ~GLBuffer();

            public:
               void SetContent(void* data, int size);
               void SetDataMode(RenderBufferDataMode dataMode);
               RenderBufferDataMode GetDataMode();

            private:
               void Bind();

            private:
               unsigned int m_desc;
               int m_size;
               Renderer* m_renderer;
               RenderBufferDataMode m_dataMode;
               unsigned int m_target;
            };

         }
      }
   }
}