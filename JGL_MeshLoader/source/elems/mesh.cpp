#include "pch.h"
#include "mesh.h"

namespace nelems
{

  void Mesh::init()
  {
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mVertexIndices.size() * sizeof(GLuint), mVertexIndices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &this->mVBO);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
    glBufferData(GL_ARRAY_BUFFER, this->mVertices.size() * sizeof(glm::vec3), mVertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  Mesh::~Mesh()
  {
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &mIBO);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
  }


  void Mesh::draw_wireframe()
  {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    // the vertices as line loop
    glDrawElements(GL_POINTS, (GLsizei) mVertexIndices.size(), GL_UNSIGNED_INT, nullptr);
    //glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mVertexIndices.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void Mesh::draw_faces()
  {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    // the vertices as line loop
    glDrawElements(GL_TRIANGLES, (GLsizei) mVertexIndices.size(), GL_UNSIGNED_INT, nullptr);
   
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}