#include "pch.h"
#include "mesh.h"

namespace nelems
{

  void Mesh::init()
  {
    create_buffers();
  }

  Mesh::~Mesh()
  {
    delete_buffers();
  }

  void Mesh::create_buffers()
  {
    glGenVertexArrays(1, &mVAO);

    glGenBuffers(1, &mIBO);
    glGenBuffers(1, &this->mVBO);

    glBindVertexArray(mVAO);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);

    glBufferData(GL_ARRAY_BUFFER, this->mVertices.size() * sizeof(glm::vec3), mVertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mVertexIndices.size() * sizeof(GLuint), mVertexIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
  }

  void Mesh::delete_buffers()
  {
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &mIBO);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
  }

  void Mesh::bind_buffers()
  {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
  }

  void Mesh::unbind_buffers()
  {
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void Mesh::draw_wireframe()
  {
    bind_buffers();

    glDrawElements(GL_POINTS, (GLsizei) mVertexIndices.size(), GL_UNSIGNED_INT, nullptr);

    unbind_buffers();
  }

  void Mesh::draw_faces()
  {
    bind_buffers();

    // the vertices as line loop
    glDrawElements(GL_TRIANGLES, (GLsizei) mVertexIndices.size(), GL_UNSIGNED_INT, nullptr);
   
    unbind_buffers();
  }
}