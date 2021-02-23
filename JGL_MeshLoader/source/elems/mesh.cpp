#include "pch.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

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

  bool Mesh::load(const std::string& filepath)
  {
    const uint32_t cMeshImportFlags =
      aiProcess_CalcTangentSpace |
      aiProcess_Triangulate |
      aiProcess_SortByPType |
      aiProcess_GenNormals |
      aiProcess_GenUVCoords |
      aiProcess_OptimizeMeshes |
      aiProcess_ValidateDataStructure;

    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(filepath.c_str(),
      cMeshImportFlags);

    if (pScene && pScene->HasMeshes())
    {
      mVertexIndices.clear();
      mVertices.clear();

      auto* mesh = pScene->mMeshes[0];

      for (uint32_t i = 0; i < mesh->mNumVertices; i++)
      {
        VertexHolder vh;
        vh.mPos = { mesh->mVertices[i].x, mesh->mVertices[i].y ,mesh->mVertices[i].z };
        vh.mNormal = { mesh->mNormals[i].x, mesh->mNormals[i].y ,mesh->mNormals[i].z };

        add_vertex(vh);
      }

      for (size_t i = 0; i < mesh->mNumFaces; i++)
      {
        aiFace face = mesh->mFaces[i];

        for (size_t j = 0; j < face.mNumIndices; j++)
          add_vertex_index(face.mIndices[j]);
      }

      init();
      return true;
    }
    return false;
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