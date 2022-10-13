#pragma once
#include "Base.h"

namespace Floppa {

   struct Color3 {
      float r, g, b;

      Color3() : r(0), g(0), b(0) {}
      Color3(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}
      Color3(float r_, float g_, float b_, float brightness) : r(r_ * brightness), g(g_ * brightness), b(b_ * brightness) {}

      static inline Color3 WHITE() { return Color3(1, 1, 1); }
      static inline Color3 BLACK() { return Color3(0, 0, 0); }
      static inline Color3 RED() { return Color3(1, 0, 0); }
      static inline Color3 GREEN() { return Color3(0, 1, 0); }
      static inline Color3 BLUE() { return Color3(0, 0, 1); }

      bool operator==(Color3 const& o) { return r == o.r && g == o.g && b == o.b; }
   };

}