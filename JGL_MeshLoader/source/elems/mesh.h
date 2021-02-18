#pragma once

#include "pch.h"

namespace nelems
{
  class Mesh
  {
  private:
    

    GLuint mVBO;
    GLuint mVAO;
    GLuint mIBO;

    std::vector<glm::vec3> mVertices;
    std::vector<GLuint> mVertexIndices;
    
  public:

    Mesh() = default;
    virtual ~Mesh();

    // Methods
    void add_vertex(const glm::vec3& vertex) { mVertices.push_back(vertex);  }

    void add_vertex_index(unsigned int vertex_idx) { mVertexIndices.push_back(vertex_idx); }

    std::vector<GLuint> GetVertexIndices() { return mVertexIndices; }

    void init();

    void bind() { glBindVertexArray(mVAO); }
    void unbind() { glBindVertexArray(0); }

    void draw_wireframe();
    void draw_faces();

  };
}

