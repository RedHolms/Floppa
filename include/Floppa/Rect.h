#pragma once
#include "Base.h"

#include "Vector2.h"

namespace Floppa {

   struct Rect {
      union {
         struct {
            long left;
            long top;
            long right;
            long bottom;
         };
      };

      Rect() : left(0), top(0), right(0), bottom(0) {}
      Rect(Position topLeft, Position bottomRight) : left(topLeft.x), top(topLeft.y), right(bottomRight.x), bottom(bottomRight.y) {}
      Rect(long left_, long top_, long right_, long bottom_) : left(left_), top(top_), right(right_), bottom(bottom_) {}

      template <typename T>
      Rect(T o) // construct from another rect struct (for example, win32's RECT)
         : left(o.left), top(o.top), right(o.right), bottom(o.bottom) {}

      long GetWidth() { return right - left; }
      long GetHeight() { return bottom - top; }

      Position GetTopLeft() { return Position(left, top); }
      Position GetTopRight() { return Position(right, top); }
      Position GetBottomLeft() { return Position(left, bottom); }
      Position GetBottomRight() { return Position(right, bottom); }
   };

}