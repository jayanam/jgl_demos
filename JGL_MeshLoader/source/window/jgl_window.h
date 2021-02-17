#pragma once

#include "main.h"
#include "mesh_import/import_obj.h"
#include "elems/mesh.h"
#include "elems/camera.h"
#include "elems/light.h"
#include "shader/shader_util.h"

using namespace nelems;
using namespace nmesh_import;
using namespace nshaders;

#include <cstdint>

struct DrawFlags
{
  bool draw_edges = true;
  bool draw_faces = true;
};

class JGLWindow
{
public:

  JGLWindow() : mIsValid(false), mWindow(nullptr)
  {}

  ~JGLWindow();

  bool init(int width, int height, const std::string& title);

  void render();

  void handle_input();


  void on_key(int key, int scancode, int action, int mods);

  void on_resize(int width, int height);

private:

  bool load_mesh();

  // Workaround til we have an input method
  const std::string mModel = "Model.obj";

  DrawFlags mDrawFlags;

  GLFWwindow* mWindow;

  std::unique_ptr<Camera> mCamera;

  std::unique_ptr<Shader> mShader;

  std::unique_ptr<Light> mLight;

  std::unique_ptr<Mesh> mMesh;

  bool mIsValid;

};


