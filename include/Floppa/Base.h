#pragma once

#ifndef _FLOPPA_DLL_EXPORT
#  if defined(_MSC_VER)
#     define _FLOPPA_DLL_EXPORT __declspec(dllexport)
#  else
#     define _FLOPPA_DLL_EXPORT
#  endif
#endif

#ifndef _FLOPPA_API
#  if defined(_FLOPPA_WIN32) && defined(_FLOPPA_SHARED)
#     define _FLOPPA_API _FLOPPA_DLL_EXPORT
#  else
#     define _FLOPPA_API
#  endif
#endif

#ifndef _FLOPPA_PRIVATE_API
#  define _FLOPPA_PRIVATE_API
#endif

#ifndef _FLOPPA_DYNAMICALLOCATED_POINTER_IMPL
#  ifdef _FLOPPA_USE_SMART_POINTERS
#     include "SmartPointer.h"
#     define _FLOPPA_DYNAMICALLOCATED_POINTER_IMPL ::Floppa::SmartPointer<T>
#  else
#     define _FLOPPA_DYNAMICALLOCATED_POINTER_IMPL T*
#  endif
#endif

#ifndef _FLOPPA_THROW_EXCEPTION
#  define _FLOPPA_THROW_EXCEPTION(ex, fn) throw ex(fn, __FILE__, __LINE__)
#  define _FLOPPA_THROW_EXCEPTION_EX(ex, fn, ...) throw ex(__VA_ARGS__, fn, __FILE__, __LINE__)
#endif

#ifndef _FLOPPA_COUNTOF
#  define _FLOPPA_COUNTOF(a) (sizeof(a)/sizeof(*a))
#endif

#ifndef _FLOPPA_MEMBEROFFSET
#  define _FLOPPA_MEMBEROFFSET(s, m) ((unsigned int)(&(((s*)nullptr)->m)))
#endif

#ifndef _FLOPPA_ENGINE_CLASS
#  define _FLOPPA_ENGINE_CLASS ::Floppa::Engine
#endif

namespace Floppa {

   class Engine;

   using OSType = int;
   enum OSType_ {
      OSType_Unknown,
      OSType_Win32
   };

#if defined(_FLOPPA_WIN32)
   constexpr OSType TargetOS = OSType_Win32;
#else
   constexpr OSType TargetOS = OSType_Unknown;
#endif

   /* Pointer that allocated with `operator new` */
   template <typename T>
   using DynamicAllocated = _FLOPPA_DYNAMICALLOCATED_POINTER_IMPL;

   /* Deallocate DynamicAllocated pointer */
   template <typename T>
   void deallocate(T*& p) {
      if (p) delete p;
      p = nullptr;
   }

   namespace NonClient {
      extern void* InstanceHandle; // Engine.cpp; Has mean on Win32 only, on other systems always nullptr
   }

}