#pragma once

#include "pch.h"

#include "render/render_base.h"
#include "vertex_holder.h"

namespace nelems
{
  class Mesh
  {
    
  public:

    Mesh() = default;

    virtual ~Mesh();

    void add_vertex(const VertexHolder& vertex) { mVertices.push_back(vertex);  }

    void add_vertex_index(unsigned int vertex_idx) { mVertexIndices.push_back(vertex_idx); }

    std::vector<unsigned int> get_vertex_indices() { return mVertexIndices; }


    void init();

    void create_buffers();

    void delete_buffers();

    void render();

    void bind();

    void unbind();

  private:
    
    // Buffers manager
    std::unique_ptr<nrender::VertexIndexBuffer> mRenderBufferMgr;
    
    // Vertices and indices
    std::vector<VertexHolder> mVertices;
    std::vector<unsigned int> mVertexIndices;

  };
}

