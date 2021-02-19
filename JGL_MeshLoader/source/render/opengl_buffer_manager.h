#pragma once

#include "pch.h"

#include "render_base.h"

namespace nrender
{
  class OpenGL_BufferManager : public RenderBufferManager
  {
  public:
    OpenGL_BufferManager() : RenderBufferManager()
    {}

    void create_buffers(const std::vector<nelems::VertexHolder>& vertices, const std::vector<unsigned int>& indices) override;

    void delete_buffers() override;

    void bind() override;

    void unbind() override;

    void draw(int index_count) override;

  };
}
