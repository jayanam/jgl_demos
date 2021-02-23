#pragma once

#include "elems/mesh.h"
#include "elems/camera.h"
#include "elems/light.h"
#include "shader/shader_util.h"

#include "render/ui_context.h"
#include "render/opengl_context.h"
#include "render/opengl_buffer_manager.h"

#include "window/window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ui/property_panel.h"
#include "ui/scene_view.h"

using namespace nui;
using namespace nelems;
using namespace nrender;
using namespace nshaders;

namespace nwindow
{
  class GLWindow : public IWindow
  {
  public:

    GLWindow() :
      mIsRunning(true), mWindow(nullptr)
    {
      mUICtx = std::make_unique<UIContext>();
      mRenderCtx = std::make_unique<OpenGL_Context>();
    }

    ~GLWindow();

    bool init(int width, int height, const std::string& title);

    void render();

    void handle_input();

    void* get_native_window() override { return mWindow; }

    void set_native_window(void* window)
    {
      mWindow = (GLFWwindow*)window;
    }

    void on_scroll(double delta) override;

    void on_key(int key, int scancode, int action, int mods) override;

    void on_resize(int width, int height) override;

    void on_close() override;

    void on_load_mesh(const std::string& file_path)
    {
      mModel = file_path;
      load_mesh();
    }

    bool is_running() { return mIsRunning; }


  private:

    bool load_mesh();

    // Workaround til we have an input method
    std::string mModel = "model.obj";

    GLFWwindow* mWindow;

    std::shared_ptr<Mesh> mMesh;

    std::unique_ptr<UIContext> mUICtx;

    std::unique_ptr<OpenGL_Context> mRenderCtx;

    // UI components
    std::unique_ptr<Property_Panel> mPropertyPanel;

    std::unique_ptr<SceneView> mSceneView;

    bool mIsRunning;

  };
}


