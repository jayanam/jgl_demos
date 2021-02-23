#include "pch.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "jgl_window.h"
#include "elems/input.h"


namespace nwindow
{
  bool GLWindow::init(int width, int height, const std::string& title)
  {
    Width = width;
    Height = height;
    Title = title;

    mRenderCtx->init(this);

    mUICtx->init(this);

    mSceneView = std::make_unique<SceneView>();

    mPropertyPanel = std::make_unique<Property_Panel>();
    mPropertyPanel->set_mesh_load_callback(BIND_FN(GLWindow::on_load_mesh));

    return mIsRunning;
  }

  GLWindow::~GLWindow()
  {
    mUICtx->end();

    mRenderCtx->end();
  }

  void GLWindow::on_resize(int width, int height)
  {
    Width = width;
    Height = height;

    mSceneView->resize(Width, Height);
    render();
  }

  void GLWindow::on_scroll(double delta)
  {
    mSceneView->on_mouse_wheel(delta);
  }

  void GLWindow::on_key(int key, int scancode, int action, int mods)
  {
    if (action == GLFW_PRESS)
    {
    }
  }

  void GLWindow::on_close()
  {
    mIsRunning = false;
  }

  void GLWindow::render()
  {

    // Render to scene to framebuffer
    mRenderCtx->pre_render();

    // TODO: render meshes in render ctx
    //mSceneView->render_elems(mMesh.get());

    // Render UI components
    mUICtx->pre_render();

    mSceneView->render();

    mPropertyPanel->render(mSceneView.get());

    mUICtx->post_render();

    handle_input();

    // Render end, swap buffers
    mRenderCtx->post_render();

  }

  void GLWindow::handle_input()
  {
    // TODO: move this and camera to scene UI component

    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
      mSceneView->on_mouse_wheel(-0.4f);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
      mSceneView->on_mouse_wheel(0.4f);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_F) == GLFW_PRESS)
    {
      mSceneView->reset_view();
    }

    double x, y;
    glfwGetCursorPos(mWindow, &x, &y);

    mSceneView->on_mouse_move(x, y, Input::GetPressedButton(mWindow));
  }

  bool GLWindow::load_mesh()
  {
   
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(mModel.c_str(),
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices);

    if (pScene->HasMeshes())
    {
      auto* mesh = pScene->mMeshes[0];

      mMesh = std::make_shared<Mesh>();

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

    mSceneView->set_mesh(mMesh);

    return true;
  }
}
