#include "pch.h"
#include "mesh.h"

namespace nelems
{

  void Mesh::init()
  {
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    glGenBuffers(1, &this->mVertexBuffer);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->mVertices.size() * sizeof(glm::vec3), mVertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  }

  Mesh::~Mesh()
  {
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
  }

  void Mesh::draw_wireframe()
  {
    // the vertices as line loop
    glDrawArrays(GL_LINE_LOOP, 0, (GLsizei) mVertexIndices.size());

  }

  void Mesh::draw_faces()
  {
    // the vertices as line loop
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mVertexIndices.size());

  }
}