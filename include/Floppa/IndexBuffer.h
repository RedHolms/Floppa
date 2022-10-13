#pragma once
#include "Base.h"

#include "Renderer.h"

namespace Floppa {

   class IndexBuffer {
   public:
      virtual ~IndexBuffer();

   public:
      virtual void SetContent(DrawIndex* indices, int count) = 0;
      virtual void SetDataMode(RenderBufferDataMode dataMode) = 0;
      virtual RenderBufferDataMode GetDataMode() = 0;
   };

}