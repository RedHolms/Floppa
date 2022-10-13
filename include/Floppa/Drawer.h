#pragma once
#include "Base.h"

#include <vector>

#include "Renderer.h"

namespace Floppa {

   class Drawer {
   public:
      _FLOPPA_API Drawer(Renderer* renderer);
      _FLOPPA_API ~Drawer();

      Drawer(Drawer const&) = delete;
      Drawer& operator=(Drawer const&) = delete;

   public:
      _FLOPPA_API bool IsAvailable();

      _FLOPPA_API void PrepareDrawData();
      _FLOPPA_API void GetDrawData(DrawData* dd);

      _FLOPPA_API void CreateBuffers(Renderer* renderer);
      _FLOPPA_API void DestroyBuffers();
      
      _FLOPPA_API void AddVertex(DrawVertex const& vertex);
      _FLOPPA_API void AddVertices(DrawVertex vertices[], int count);

      inline void AddVertices(std::vector<DrawVertex> vertices) { AddVertices(vertices.data(), static_cast<int>(vertices.size())); }

   private:
      std::vector<DrawVertex> m_vertices;
      std::vector<DrawIndex> m_indices;
      DynamicAllocated<VertexBuffer> m_vertBuff;
      DynamicAllocated<IndexBuffer> m_idxBuff;
   };

}