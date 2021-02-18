#pragma once

#include "pch.h"

namespace nelems
{
  class Mesh
  {
    
  public:

    Mesh() : mVBO{0}, mVAO{0}, mIBO{0}
    {
    }

    virtual ~Mesh();

    void add_vertex(const glm::vec3& vertex) { mVertices.push_back(vertex);  }

    void add_vertex_index(unsigned int vertex_idx) { mVertexIndices.push_back(vertex_idx); }

    std::vector<GLuint> GetVertexIndices() { return mVertexIndices; }

    void init();

    void create_buffers();

    void delete_buffers();

    void draw_wireframe();

    void draw_faces();

    void bind_buffers();

    void unbind_buffers();

  private:
    
    // Buffers
    GLuint mVBO;
    GLuint mVAO;
    GLuint mIBO;

    // Vertices and indices
    std::vector<glm::vec3> mVertices;
    std::vector<GLuint> mVertexIndices;

  };
}

