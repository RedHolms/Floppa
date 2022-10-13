#pragma once
#include "Base.h"

namespace Floppa {

   struct UDim {
      float scale;
      float offset;

      UDim() : scale(0), offset(0) {}
      UDim(float scale_, float offset_) : scale(scale_), offset(offset_) {}
   };

   struct UDim2 {
      union {
         struct { UDim x, y; };
         struct { UDim width, height; };
      };

      UDim2() : x(), y() {}
      UDim2(UDim x_, UDim y_) : x(x_), y(y_) {}
      UDim2(float xScale, float xOffset, float yScale, float yOffset) : x(xScale, xOffset), y(yScale, yOffset) {}
   };

}