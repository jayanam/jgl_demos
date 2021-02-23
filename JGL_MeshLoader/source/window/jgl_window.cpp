#include "pch.h"

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

    mPropertyPanel->set_mesh_load_callback(
      [this](std::string filepath) { mSceneView->load_mesh(filepath); });

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
    // Clear the view
    mRenderCtx->pre_render();

    // Initialize UI components
    mUICtx->pre_render();

    // render scene to framebuffer and add it to scene view
    mSceneView->render();

    mPropertyPanel->render(mSceneView.get());

    // Render the UI 
    mUICtx->post_render();

    // Render end, swap buffers
    mRenderCtx->post_render();

    handle_input();
  }

  void GLWindow::handle_input()
  {
    // TODO: move this and camera to scene UI component?

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
}
