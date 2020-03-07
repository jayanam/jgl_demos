#pragma once

#include "main.h"
#include "mesh_import/import_obj.h"
#include "elems/mesh.h"
#include "elems/camera.h"
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

  JGLWindow() = default;

  ~JGLWindow();

  bool init(int width, int height, const std::string& title);

  void render();

  void on_key(int key, int scancode, int action, int mods);


private:

  DrawFlags mDrawFlags;

  GLFWwindow* mWindow;

  std::unique_ptr<Camera> mCamera;

  std::unique_ptr<ShaderUtil> mShader;

  bool mIsValid;

};


