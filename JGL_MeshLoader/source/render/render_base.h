#pragma once

#include "elems/vertex_holder.h"

namespace nrender
{
  class RenderBufferManager
  {
  public:
    RenderBufferManager() : mVBO{ 0 }, mVAO{ 0 }, mIBO{ 0 }
    {}

    virtual void create_buffers(const std::vector<nelems::VertexHolder>& vertices, const std::vector<unsigned int>& indices) = 0;

    virtual void delete_buffers() = 0;

    virtual void bind() = 0;

    virtual void unbind() = 0;

    virtual void draw(int index_count) = 0;

  protected:
    GLuint mVBO;
    GLuint mVAO;
    GLuint mIBO;
  };
}
