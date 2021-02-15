#pragma once

namespace nelems
{
  class Face
  {
  private:
    std::vector<GLuint> mVertexIndices;

  public:

    void add_vertex_index(GLuint index) { mVertexIndices.push_back(index); }

  };
}

