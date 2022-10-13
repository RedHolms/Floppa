#pragma once
#include "Base.h"

#include "Renderer.h"

namespace Floppa {

   class VertexBuffer {
   public:
      virtual ~VertexBuffer();
   
   public:
      virtual void SetContent(DrawVertex* vertices, int count) = 0;
      virtual void SetDataMode(RenderBufferDataMode dataMode) = 0;
      virtual RenderBufferDataMode GetDataMode() = 0;
   };

}