#pragma once

#include "elems/mesh.h"
#include "elems/camera.h"
#include "elems/light.h"
#include "shader/shader_util.h"

#include "render/ui_context.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace nelems;
using namespace nrender;
using namespace nshaders;

class JGLWindow
{
public:

  JGLWindow() : 
    mIsValid(false), mWindow(nullptr), mWidth(0), mHeight(0)
  {
    mUICtx = std::make_unique<UIContext>();
  }

  ~JGLWindow();
   
  bool init(int width, int height, const std::string& title);

  void render();

  void handle_input();

  void on_key(int key, int scancode, int action, int mods);

  void on_resize(int width, int height);

private:

  bool load_mesh();

  // Workaround til we have an input method
  const std::string mModel = "model.obj";

  GLFWwindow* mWindow;

  std::unique_ptr<Camera> mCamera;

  std::unique_ptr<Shader> mShader;

  std::unique_ptr<Light> mLight;

  std::unique_ptr<Mesh> mMesh;

  std::unique_ptr<UIContext> mUICtx;

  int mWidth, mHeight;

  bool mIsValid;

};


