#include <Floppa/Drawer.h>

#include <Floppa/Renderer.h>
#include <Floppa/VertexBuffer.h>
#include <Floppa/IndexBuffer.h>

namespace Floppa {

   Drawer::Drawer(Renderer* renderer) {
      m_vertBuff = nullptr;
      m_idxBuff = nullptr;

      CreateBuffers(renderer);
   }

   Drawer::~Drawer() {
      DestroyBuffers();
   }

   bool Drawer::IsAvailable() {
      return ((VertexBuffer*)m_vertBuff) != nullptr;
   }

   void Drawer::PrepareDrawData() {
      if (!IsAvailable()) return;

      m_vertBuff->SetContent(m_vertices.data(), (int)m_vertices.size());
      m_idxBuff->SetContent(m_indices.data(), (int)m_indices.size());
   }

   void Drawer::GetDrawData(DrawData* dd) {
      if (!IsAvailable()) return;

      dd->vertices = m_vertBuff;
      dd->indices = m_idxBuff;
   }

   void Drawer::CreateBuffers(Renderer* renderer) {
      if (!m_vertBuff)
         m_vertBuff = renderer->CreateVertexBuffer();

      if (!m_idxBuff)
         m_idxBuff = renderer->CreateIndexBuffer();
   }

   void Drawer::DestroyBuffers() {
      if (m_vertBuff)
         deallocate(m_vertBuff);

      if (m_idxBuff)
         deallocate(m_idxBuff);
   }

   void Drawer::AddVertex(DrawVertex const& vertex) {
      // check is the same vertex already exist
      for (int i = (int)m_vertices.size() - 1; i >= 0; --i) {
         if (m_vertices[i] == vertex) {
            // if the same vertex alredy exist, insert only index
            m_indices.push_back(i);
            return;
         }
      }

      // if this vertex is unique, add it and index
      m_vertices.push_back(vertex);
      m_indices.push_back((DrawIndex)m_vertices.size() - 1);
   }

   void Drawer::AddVertices(DrawVertex vertices[], int count) {
      for (int i = 0; i < count; ++i) {
         AddVertex(vertices[i]);
      }
   }
     
}