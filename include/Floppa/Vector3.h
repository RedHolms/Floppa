#pragma once

#include "Math.h"

namespace Floppa {

   template <typename T>
   struct tVector3 {
      T x, y, z;

      using type = tVector3<T>;
      using element_type = T;

      tVector3() : x(0), y(0), z(0) {}
      tVector3(T v) : x(v), y(v), z(v) {}
      tVector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

      static constexpr tVector3 Zero() { return tVector3(0, 0, 0); }

      tVector3 operator+(tVector3 const& o) { return tVector3(x + o.x, y + o.y, z + o.z); }
      tVector3 operator-(tVector3 const& o) { return tVector3(x - o.x, y - o.y, z - o.z); }
      tVector3 operator*(T s) { return tVector3(x * s, y * s, z * s); }
      tVector3 operator/(T s) { return tVector3(x / s, y / s, z / s); }

      tVector3& operator+=(tVector3 const& o) { x += o.x; y += o.y; z += o.z; return *this; }
      tVector3& operator-=(tVector3 const& o) { x += o.x; y += o.y; z += o.z; return *this; }
      tVector3& operator*=(T s) { x *= s; y *= s; z *= s; return *this; }
      tVector3& operator/=(T s) { x /= s; y /= s; z /= s; return *this; }

      bool operator==(tVector3 const& o) { return x == o.x && y == o.y && z == o.z; }

      float Length() {
         float fx = static_cast<float>(x);
         float fy = static_cast<float>(y);
         float fz = static_cast<float>(z);

         return SquareRoot((fx * fx) + (fy * fy) + (fz * fz));
      }
   };

   using Vector3 = tVector3<float>;

}