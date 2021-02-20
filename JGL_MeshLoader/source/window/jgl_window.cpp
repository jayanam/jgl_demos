#include "pch.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "jgl_window.h"
#include "elems/input.h"
#include "application.h"

namespace nwindow
{
  bool JGLWindow::init(int width, int height, const std::string& title)
  {
    Width = width;
    Height = height;
    Title = title;

    mRenderCtx->init(this);

    mUICtx->init(this);

    auto aspect = (float)width / (float)height;
    mShader = std::make_unique<Shader>();
    mShader->load("shaders/vs.shader", "shaders/fs.shader");

    mCamera = std::make_unique<Camera>(glm::vec3(0, 0, 3), 45.0f, aspect, 0.1f, 100.0f);

    mLight = std::make_unique<Light>();

    load_mesh();

    mShader->use();

    return mIsRunning;
  }

  JGLWindow::~JGLWindow()
  {
    mUICtx->end();

    mShader->unload();

    mRenderCtx->end();

    if (mShader)
    {
      mShader->unload();
    }
  }

  void JGLWindow::on_resize(int width, int height)
  {
    Width = width;
    Height = height;

    mCamera->set_aspect((float)width / (float)height);

    render();
  }

  void JGLWindow::on_key(int key, int scancode, int action, int mods)
  {
    if (action == GLFW_PRESS)
    {
    }
  }

  void JGLWindow::on_close()
  {
    mIsRunning = false;
  }

  void JGLWindow::render()
  {
    mCamera->update(mShader.get());

    mLight->update(mShader.get());

    mRenderCtx->pre_render();

    // TODO: render all meshes / models here
    if (mMesh)
    {
      mMesh->render();
    }

    mUICtx->pre_render();

    // TODO: render UI components

    mUICtx->post_render();

    handle_input();

    mRenderCtx->post_render();

  }

  void JGLWindow::handle_input()
  {
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
      mCamera->set_distance(-0.1f);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
      mCamera->set_distance(0.1f);
    }

    double x, y;
    glfwGetCursorPos(mWindow, &x, &y);

    mCamera->on_mouse_move(x, y, Input::GetPressedButton(mWindow));

  }

  bool JGLWindow::load_mesh()
  {
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(mModel.c_str(),
      aiProcess_CalcTangentSpace |
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_SortByPType);

    if (pScene->HasMeshes())
    {
      auto* mesh = pScene->mMeshes[0];

      mMesh = std::make_unique<Mesh>();

      for (uint32_t i = 0; i < mesh->mNumVertices; i++)
      {
        VertexHolder vh;
        vh.mPos = { mesh->mVertices[i].x, mesh->mVertices[i].y ,mesh->mVertices[i].z };
        vh.mNormal = { mesh->mNormals[i].x, mesh->mNormals[i].y ,mesh->mNormals[i].z };

        mMesh->add_vertex(vh);
      }

      for (size_t i = 0; i < mesh->mNumFaces; i++)
      {
        aiFace face = mesh->mFaces[i];

        for (size_t j = 0; j < face.mNumIndices; j++)
          mMesh->add_vertex_index(face.mIndices[j]);
      }
    }

    mMesh->init();
    return true;
  }
}
