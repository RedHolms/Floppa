#pragma once
#include "Base.h"

#include "Exceptions.h"
#include "Vector3.h"
#include "Color.h"

namespace Floppa {

   class VertexBuffer;
   class IndexBuffer;
   class Drawer;
   class Window;

   using RenderBufferDataMode = int;
   enum RenderBufferDataMode_ {
      RenderBufferDataMode_Dynamic,
      RenderBufferDataMode_Static
   };

   struct DrawVertex {
      Vector3 pos;
      Color3 color;

      bool operator==(DrawVertex const& o) { return pos == o.pos && color == o.color; }
   };

   using DrawIndex = unsigned int;

   struct DrawData {
      VertexBuffer* vertices;
      IndexBuffer* indices;
   };

   using RendererImpl = int;
   enum RendererImpl_ {
      RendererImpl_OpenGL3
   };

   class Renderer {
   public:
      _FLOPPA_API static DynamicAllocated<Renderer> New(RendererImpl tp, Window* window);

      virtual ~Renderer();

   public:
      virtual RendererImpl GetRendererImpl() = 0;

      virtual void OnWindowResized() = 0;

      virtual void Render() = 0;
      virtual void SwapBuffers() = 0;

      virtual DynamicAllocated<VertexBuffer> CreateVertexBuffer() = 0;
      virtual DynamicAllocated<IndexBuffer> CreateIndexBuffer() = 0;

      template <typename T, typename... AllocationArgs>
      T* CreateDrawer(AllocationArgs&&... args) {
         DynamicAllocated<T> drawer = new T(this, args...);
         T* p = drawer;

         AttachDrawer(std::move(drawer));
         return p;
      }

   private:
      virtual void AttachDrawer(DynamicAllocated<Drawer> drawer) = 0;
   };

}

namespace Floppa {

   class RendererException : public BaseException {
   public:
      RendererException(RendererImpl rendererImpl, std::string information, std::string calledMethod, const char* file, int line)
         : m_rendererImpl(rendererImpl), BaseException(information, calledMethod, file, line) {}

      RendererImpl GetRendererImpl() { return m_rendererImpl; }

   private:
      RendererImpl m_rendererImpl;
   };

   class ShaderCompilingException : public RendererException {
   public:
      ShaderCompilingException(const char* shaderName, std::string errorMsg, RendererImpl rendererImpl, std::string calledMethod, const char* file, int line)
         : RendererException(rendererImpl, std::string("Failed to compile ") + shaderName + " shader: " + errorMsg, calledMethod, file, line) {}
   };

   class ShaderProgramLinkingException : public RendererException {
   public:
      ShaderProgramLinkingException(std::string errorMsg, RendererImpl rendererImpl, std::string calledMethod, const char* file, int line)
         : RendererException(rendererImpl, std::string("Failed to link shader program: ") + errorMsg, calledMethod, file, line) {}
   };

}