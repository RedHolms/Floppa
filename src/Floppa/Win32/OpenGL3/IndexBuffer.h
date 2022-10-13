#pragma once
#include <Floppa/Base.h>

#include <Floppa/IndexBuffer.h>

#include "GLBuffer.h"

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            class Renderer;

            class IndexBuffer : public Floppa::IndexBuffer, public GLBuffer {
               friend Renderer;
            
            public:
               IndexBuffer(Renderer* renderer);
               ~IndexBuffer();

            public:
               void SetContent(DrawIndex* indices, int count);
               void SetDataMode(RenderBufferDataMode dataMode);
               RenderBufferDataMode GetDataMode();
            };

         }
      }
   }
}