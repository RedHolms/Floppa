#include "VertexBuffer.h"

#include <gl/glew.h>

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            VertexBuffer::VertexBuffer(Renderer* renderer) : GLBuffer(renderer, GL_ARRAY_BUFFER) {}
            VertexBuffer::~VertexBuffer() {}

            void VertexBuffer::SetContent(DrawVertex* vertices, int count) {
               GLBuffer::SetContent(vertices, sizeof(DrawVertex) * count);
            }

            void VertexBuffer::SetDataMode(RenderBufferDataMode dataMode) {
               GLBuffer::SetDataMode(dataMode);
            }

            RenderBufferDataMode VertexBuffer::GetDataMode() {
               return GLBuffer::GetDataMode();
            }

         }
      }
   }
}