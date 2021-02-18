#include "pch.h"
#include "opengl_buffer_manager.h"


void OpenGL_Buffer_Manager::create_buffers(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices)
{
  glGenVertexArrays(1, &mVAO);

  glGenBuffers(1, &mIBO);
  glGenBuffers(1, &mVBO);

  glBindVertexArray(mVAO);

  // Load data into vertex buffers
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
}

void OpenGL_Buffer_Manager::bind_buffers()
{
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
}

void OpenGL_Buffer_Manager::unbind_buffers()
{
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}