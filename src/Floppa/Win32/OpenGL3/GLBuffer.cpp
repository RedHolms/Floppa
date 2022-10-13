#include "GLBuffer.h"

#include <gl/glew.h>

#include "Renderer.h"

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            GLBuffer::GLBuffer(Renderer* renderer, unsigned int target) {
               m_desc = 0;
               m_size = 0;
               m_renderer = renderer;
               m_dataMode = RenderBufferDataMode_Dynamic;
               m_target = target;

               m_renderer->SelectContext();
               glGenBuffers(1, &m_desc);
            }

            GLBuffer::~GLBuffer() {
               glDeleteBuffers(1, &m_desc);
            }

            void GLBuffer::SetContent(void* data, int size) {
               m_renderer->SelectContext();

               GLenum buffer_usage = 0;
               switch (m_dataMode) {
               case RenderBufferDataMode_Static: buffer_usage = GL_STATIC_DRAW; break;
               default: m_dataMode = RenderBufferDataMode_Dynamic;
               case RenderBufferDataMode_Dynamic: buffer_usage = GL_DYNAMIC_DRAW; break;
               }

               Bind();
               glBufferData(m_target, size, data, buffer_usage);
               m_size = size;
            }

            void GLBuffer::SetDataMode(RenderBufferDataMode dataMode) {
               m_dataMode = dataMode;
            }

            RenderBufferDataMode GLBuffer::GetDataMode() {
               return m_dataMode;
            }

            void GLBuffer::Bind() {
               glBindBuffer(m_target, m_desc);
            }

         }
      }
   }
}