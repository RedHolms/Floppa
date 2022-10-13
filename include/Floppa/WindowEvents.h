#pragma once

#include "Vector2.h"

namespace Floppa {

   using WindowEventType = int;
   enum WindowEventType_ {
      WindowEventType_WindowResized,
   };

   class WindowEvent {
   public:
      WindowEvent(WindowEventType tp)
         : m_evType(tp) {}

      virtual WindowEventType GetEventType() { return m_evType; }

   private:
      WindowEventType m_evType;
   };

   /* === Events list === */

   class WindowResizedEvent : public WindowEvent {
   public:
      WindowResizedEvent(long new_width, long new_height)
         : m_new({ new_width, new_height }), WindowEvent(WindowEventType_WindowResized) {}

      WindowResizedEvent(Size new_size)
         : m_new(new_size), WindowEvent(WindowEventType_WindowResized) {}

      Size GetNewSize() { return m_new; }

   private:
      Size m_new;
   };

}