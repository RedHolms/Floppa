#include "IndexBuffer.h"

#include <gl/glew.h>

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            IndexBuffer::IndexBuffer(Renderer* renderer) : GLBuffer(renderer, GL_ELEMENT_ARRAY_BUFFER) {}
            IndexBuffer::~IndexBuffer() {}

            void IndexBuffer::SetContent(DrawIndex* indices, int count) {
               GLBuffer::SetContent(indices, sizeof(DrawIndex) * count);
            }

            void IndexBuffer::SetDataMode(RenderBufferDataMode dataMode) {
               GLBuffer::SetDataMode(dataMode);
            }

            RenderBufferDataMode IndexBuffer::GetDataMode() {
               return GLBuffer::GetDataMode();
            }

         }
      }
   }
}