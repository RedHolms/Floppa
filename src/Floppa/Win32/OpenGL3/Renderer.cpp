#include "Renderer.h"

#include <assert.h>

#include <vector>

#include <gl/glew.h>
#include <Windows.h>

#include <Floppa/Window.h>
#include <Floppa/Drawer.h>
#include <Floppa/Rect.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

// Shaders
static const char* Floppa_OpenGL3Impl_Vertex_Shader =
R"(
#version 330 core

layout (location = 0) in vec3 viPos;
layout (location = 1) in vec3 viColor;

out vec3 vertexColor;

void main() {
   gl_Position = vec4(viPos, 1.0);
   vertexColor = viColor;
}
)" "\0";

static const char* Floppa_OpenGL3Impl_Fragment_Shader =
R"(
#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main() {
   FragColor = vec4(vertexColor, 1.0);
} 
)" "\0";

namespace Floppa {
   namespace Impl {
      namespace Win32 {
         namespace OpenGL3 {

            struct Renderer_Data {
               std::vector<DynamicAllocated<Drawer>> drawers;
               HWND rawWindowHandle;
               HDC deviceContextHandle;
               HGLRC renderingContextHandle;
               GLuint shaderProgram;
            };

            Renderer::Renderer(Window* window) {
               m = new Renderer_Data;

               m->rawWindowHandle = reinterpret_cast<HWND>(window->GetSystemHandle().win32Handle);
               m->deviceContextHandle = GetDC(m->rawWindowHandle);

               SetupPixelFormat();
               CreateContext();

               InitOpenGL();
               CreateOpenGLObjects();

               OnWindowResized();
            }

            Renderer::~Renderer() {
               DestroyOpenGLObjects();
               DestroyContext();

               deallocate(m);
            }

            RendererImpl Renderer::GetRendererImpl() {
               return RendererImpl_OpenGL3;
            }

            void Renderer::OnWindowResized() {
               Rect clRect;
               GetClientRect(m->rawWindowHandle, (LPRECT)&clRect);

               glViewport(0, 0, clRect.GetWidth(), clRect.GetHeight());
            }

            void Renderer::SetupRenderState() {
               glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            }

            void Renderer::Render() {
               SetupRenderState();

               glClear(GL_COLOR_BUFFER_BIT);

               for (int i = static_cast<int>(m->drawers.size()) - 1; i >= 0; --i) {
                  DynamicAllocated<Drawer>& drawer = m->drawers[i];

                  drawer->PrepareDrawData();

                  DrawData dd;
                  drawer->GetDrawData(&dd);

                  VertexBuffer* vertices = reinterpret_cast<VertexBuffer*>(dd.vertices);
                  IndexBuffer* indices = reinterpret_cast<IndexBuffer*>(dd.indices);
                  
                  glUseProgram(m->shaderProgram);
                  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DrawVertex), NULL);
                  glEnableVertexAttribArray(0);
                  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DrawVertex), (void*)(_FLOPPA_MEMBEROFFSET(DrawVertex, color)));
                  glEnableVertexAttribArray(1);
                  vertices->Bind();
                  indices->Bind();
                  glDrawElements(GL_TRIANGLES, indices->m_size / sizeof(DrawIndex), GL_UNSIGNED_INT, NULL);
               }
            }

            void Renderer::SwapBuffers() {
               ::SwapBuffers(m->deviceContextHandle);
            }

            DynamicAllocated<Floppa::VertexBuffer> Renderer::CreateVertexBuffer() {
               return new VertexBuffer(this);
            }

            DynamicAllocated<Floppa::IndexBuffer> Renderer::CreateIndexBuffer() {
               return new IndexBuffer(this);
            }

            void Renderer::AttachDrawer(DynamicAllocated<Drawer> drawer) {
               m->drawers.push_back(std::move(drawer));
            }

            void Renderer::SelectContext() {
               wglMakeCurrent(m->deviceContextHandle, m->renderingContextHandle);
            }

            void Renderer::SetupPixelFormat() {
               PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { 0 };
               int pixelFormat;

               ZeroMemory(&pixelFormatDescriptor, sizeof(PIXELFORMATDESCRIPTOR));
               pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
               pixelFormatDescriptor.nVersion = 1;
               pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
               pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
               pixelFormatDescriptor.cColorBits = 32;
               pixelFormatDescriptor.cDepthBits = 24;
               pixelFormatDescriptor.cAlphaBits = 8;
               pixelFormatDescriptor.dwLayerMask = PFD_MAIN_PLANE;

               pixelFormat = ChoosePixelFormat(m->deviceContextHandle, &pixelFormatDescriptor);

               // todo make normal error handling
               assert(pixelFormat && "failed to choose pixel format");
               assert(SetPixelFormat(m->deviceContextHandle, pixelFormat, &pixelFormatDescriptor) && "failed to set pixel format");
            }

            void Renderer::CreateContext() {
               m->renderingContextHandle = wglCreateContext(m->deviceContextHandle);
            }

            void Renderer::DestroyContext() {
               DeleteDC(m->deviceContextHandle);
               m->deviceContextHandle = NULL;

               wglDeleteContext(m->renderingContextHandle);
               m->renderingContextHandle = NULL;
            }

            void Renderer::InitOpenGL() {
               SelectContext();

               glewExperimental = GL_TRUE;
               assert(glewInit() == GLEW_OK);
            }

            void Renderer::CreateOpenGLObjects() {
               SelectContext();

               GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
               glShaderSource(vertexShader, 1, &Floppa_OpenGL3Impl_Vertex_Shader, NULL);
               glCompileShader(vertexShader);
               CheckShader(vertexShader, "vertex");

               GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
               glShaderSource(fragmentShader, 1, &Floppa_OpenGL3Impl_Fragment_Shader, NULL);
               glCompileShader(fragmentShader);
               CheckShader(fragmentShader, "fragment");

               m->shaderProgram = glCreateProgram();
               glAttachShader(m->shaderProgram, vertexShader);
               glAttachShader(m->shaderProgram, fragmentShader);
               glLinkProgram(m->shaderProgram);
               CheckProgram(m->shaderProgram);

               glDetachShader(m->shaderProgram, vertexShader);
               glDetachShader(m->shaderProgram, fragmentShader);
               glDeleteShader(vertexShader);
               glDeleteShader(fragmentShader);

               // Create buffers in all drawer if OpenGL objects was destroyed at runtime
               for (auto& drawer : m->drawers)
                  if (!drawer->IsAvailable())
                     drawer->CreateBuffers(this);
            }

            void Renderer::DestroyOpenGLObjects() {
               SelectContext();

               for (auto& drawer : m->drawers)
                  drawer->DestroyBuffers();

               glDeleteProgram(m->shaderProgram);
               m->shaderProgram = 0;
            }

            void Renderer::CheckShader(unsigned int desc, const char* name) {
               GLint success;
               char error_buf[512];

               glGetShaderiv(desc, GL_COMPILE_STATUS, &success);
               if (!success) {
                  glGetShaderInfoLog(desc, sizeof(error_buf), NULL, error_buf);
                  _FLOPPA_THROW_EXCEPTION_EX(ShaderCompilingException, "Renderer::CheckShader()", name, error_buf, RendererImpl_OpenGL3);
               }
            }

            void Renderer::CheckProgram(unsigned int desc) {
               GLint success;
               char error_buf[256];

               glGetProgramiv(desc, GL_LINK_STATUS, &success);
               if (!success) {
                  glGetProgramInfoLog(desc, sizeof(error_buf), NULL, error_buf);
                  _FLOPPA_THROW_EXCEPTION_EX(ShaderProgramLinkingException, "Renderer::CheckProgram()", error_buf, RendererImpl_OpenGL3);
               }
            }

         }
      }
   }
}