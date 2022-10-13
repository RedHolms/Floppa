#pragma once

#include "Math.h"

namespace Floppa {

   template <typename T>
   struct tVector2 {
      T x, y;

      using type = tVector2<T>;
      using element_type = T;

      tVector2() : x(0), y(0) {}
      tVector2(T v) : x(v), y(v) {}
      tVector2(T x_, T y_) : x(x_), y(y_) {}

      static constexpr tVector2 Zero() { return tVector2(0, 0); }

      tVector2 operator+(tVector2 const& o) { return tVector2(x + o.x, y + o.y); }
      tVector2 operator-(tVector2 const& o) { return tVector2(x - o.x, y - o.y); }
      tVector2 operator*(T s) { return tVector2(x * s, y * s); }
      tVector2 operator/(T s) { return tVector2(x / s, y / s); }

      tVector2& operator+=(tVector2 const& o) { x += o.x; y += o.y; return *this; }
      tVector2& operator-=(tVector2 const& o) { x += o.x; y += o.y; return *this; }
      tVector2& operator*=(T s) { x *= s; y *= s; return *this; }
      tVector2& operator/=(T s) { x /= s; y /= s; return *this; }

      float Length() {
         float fx = static_cast<float>(x);
         float fy = static_cast<float>(y);

         return SquareRoot((fx * fx) + (fy * fy));
      }
   };

   using Vector2 = tVector2<float>;
   using Size = tVector2<long>;
   using Position = tVector2<long>;

}