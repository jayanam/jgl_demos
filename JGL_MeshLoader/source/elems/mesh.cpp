#include "pch.h"
#include "mesh.h"

#include "render/opengl_buffer_manager.h"

namespace nelems
{
  void Mesh::init()
  {
    mRenderBufferMgr = std::make_unique<nrender::OpenGL_VertexIndexBuffer>();

    create_buffers();
  }

  Mesh::~Mesh()
  {
    delete_buffers();
  }

  void Mesh::create_buffers()
  {
    mRenderBufferMgr->create_buffers(mVertices, mVertexIndices);
  }

  void Mesh::delete_buffers()
  {
    mRenderBufferMgr->delete_buffers();
  }

  void Mesh::bind()
  {
    mRenderBufferMgr->bind();
  }

  void Mesh::unbind()
  {
    mRenderBufferMgr->unbind();
  }

  void Mesh::render()
  {
    mRenderBufferMgr->draw((int) mVertexIndices.size());
  }
}