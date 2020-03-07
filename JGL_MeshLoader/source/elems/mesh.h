#pragma once

namespace nelems
{
  class Mesh
  {
  private:
    
    std::vector<glm::vec3> mVertices;

    GLuint mVertexBuffer;
    GLuint mVertexArray;
    std::vector<GLuint> mVertexIndices;


  public:



    Mesh() = default;
    virtual ~Mesh();


    // Methods
    void add_vertex(glm::vec3 vertex) { mVertices.push_back(vertex);  }

    void add_vertex_index(unsigned int vertex_idx) { mVertexIndices.push_back(vertex_idx); }

    std::vector<GLuint> GetVertexIndices() { return mVertexIndices; }

    void init();

    void bind() { glBindVertexArray(mVertexArray); }
    void unbind() { glBindVertexArray(0); }

    void draw_wireframe();
    void draw_faces();

  };
}

