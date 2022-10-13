#pragma once
#include <Floppa/Base.h>

#include <Floppa/VertexBuffer.h>

#include "GLBuffer.h"

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            class Renderer;

            class VertexBuffer : public Floppa::VertexBuffer, public GLBuffer {
               friend Renderer;

            public:
               VertexBuffer(Renderer* renderer);
               ~VertexBuffer();

            public:
               void SetContent(DrawVertex* vertices, int count);
               void SetDataMode(RenderBufferDataMode dataMode);
               RenderBufferDataMode GetDataMode();
            };

         }
      }
   }
}