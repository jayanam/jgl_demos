#pragma once

#include "pch.h"

class OpenGL_Buffer_Manager
{
public:
  OpenGL_Buffer_Manager() : mVBO{ 0 }, mVAO{ 0 }, mIBO{ 0 }
  {}

  void create_buffers(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices);

  void bind_buffers();

  void unbind_buffers();

private:
  GLuint mVBO;
  GLuint mVAO;
  GLuint mIBO;
};
