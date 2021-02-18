#pragma once

#include "pch.h"

class OpenGL_Buffer_Manager
{
public:
  OpenGL_Buffer_Manager() : mVBO{ 0 }, mVAO{ 0 }, mIBO{ 0 }
  {}

private:
  GLuint mVBO;
  GLuint mVAO;
  GLuint mIBO;
};
