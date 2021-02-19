#include "pch.h"
#include "opengl_buffer_manager.h"
#
namespace nrender
{

  void OpenGL_BufferManager::create_buffers(const std::vector<nelems::VertexHolder>& vertices, const std::vector<unsigned int>& indices)
  {
    glGenVertexArrays(1, &mVAO);

    glGenBuffers(1, &mIBO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(nelems::VertexHolder), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nelems::VertexHolder), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(nelems::VertexHolder), (void*)offsetof(nelems::VertexHolder, mNormal));

    glBindVertexArray(0);

  }

  void OpenGL_BufferManager::delete_buffers()
  {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &mIBO);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
  }

  void OpenGL_BufferManager::bind()
  {
    glBindVertexArray(mVAO);
  }

  void OpenGL_BufferManager::unbind()
  {
    glBindVertexArray(0);
  }

  void OpenGL_BufferManager::draw(int index_count)
  {
    bind();

    // the vertices as line loop
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);

    unbind();
  }
}