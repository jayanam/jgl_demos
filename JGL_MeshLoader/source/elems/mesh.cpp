#include "pch.h"
#include "mesh.h"

#include "render/opengl_buffer_manager.h"

namespace nelems
{
  void Mesh::init()
  {
    mRenderBufferMgr = std::make_unique<nrender::OpenGL_BufferManager>();

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

  void Mesh::draw_wireframe()
  {
    // TODO: Special method to see the wireframe
    // Can be moved to shader e.g. ?
    //bind();

    //glDrawElements(GL_POINTS, (GLsizei) mVertexIndices.size(), GL_UNSIGNED_INT, nullptr);

    //unbind();
  }

  void Mesh::draw_faces()
  {
    mRenderBufferMgr->draw((int) mVertexIndices.size());
  }
}