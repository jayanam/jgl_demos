#include "pch.h"
#include "jgl_window.h"

// Global window callbacks
static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  JGLWindow* pWindow = static_cast<JGLWindow*>(glfwGetWindowUserPointer(window));
  pWindow->on_key(key, scancode, action, mods);
}


static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
  JGLWindow* pWindow = static_cast<JGLWindow*>(glfwGetWindowUserPointer(window));
  pWindow->on_resize(width, height);
}


bool JGLWindow::init(int width, int height, const std::string& title)
{
  mIsValid = true;

  /* Initialize the library */
  if (!glfwInit())
  {
    fprintf(stderr, "Error: GLFW Window couldn't be initialized\n");
    mIsValid = false;
  }

  // Create the window and store this window as window pointer
  // so that we can use it in callback functions
  mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!mWindow)
  {
    fprintf(stderr, "Error: GLFW Window couldn't be created\n");
    mIsValid = false;
  }

  glfwSetWindowUserPointer(mWindow, this);
  glfwSetKeyCallback(mWindow, on_key_callback);

  glfwSetWindowSizeCallback(mWindow, on_window_size_callback);
  glfwMakeContextCurrent(mWindow);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    mIsValid = false;
  }

  glEnable(GL_DEPTH_TEST);

  auto aspect = (float)width / (float)height;
  mShader = std::make_unique<Shader>();
  mShader->load("shaders/vs.shader", "shaders/fs.shader");
  
  mCamera = std::make_unique<Camera>(glm::vec3(0, 0, 3), 45.0f, aspect, 0.1f, 100.0f);

  mLight = std::make_unique<Light>(0.0f, 0.5f, 1.0f, 5.0f);


  return mIsValid;
}

JGLWindow::~JGLWindow()
{
  if (mIsValid)
  {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
  }

  if (mShader)
  {
    mShader->unload();
  }
}

void JGLWindow::on_resize(int width, int height)
{
  mCamera->set_aspect((float)width / (float)height);
  glViewport(0, 0, width, height);
}

void JGLWindow::on_key(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    // Toggle draw faces
    if (key == GLFW_KEY_F)
    {
      mDrawFlags.draw_faces = !mDrawFlags.draw_faces;
    }

    // Toggle draw edges
    if (key == GLFW_KEY_E)
    {
      mDrawFlags.draw_edges = !mDrawFlags.draw_edges;
    }
  }
}

void JGLWindow::render()
{
  load_mesh();

    /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(mWindow))
  {
    mShader->use();
    mShader->update_camera(mCamera.get());

    mShader->update_light(mLight.get());

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mMesh)
    {
      // Draw the mesh
      if (mDrawFlags.draw_faces)
      {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f);

        glm::vec4 vColor{ 0.7f, 0.1f, 0.1f, 1.0f };
        mShader->set_vec4(vColor, "color");
        mMesh->draw_faces();
        glDisable(GL_POLYGON_OFFSET_FILL);
      }

      if (mDrawFlags.draw_edges)
      {
        glm::vec4 vColor{ 1.0f, 1.0f, 1.0f, 1.0f };
        mShader->set_vec4(vColor, "color");
        mMesh->draw_wireframe();
      }
    }

    glfwSwapBuffers(mWindow);

    glfwPollEvents();

    handle_input();
  }

  mShader->unload();
}

void JGLWindow::handle_input()
{
  if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
  {
    mCamera->set_distance(-0.1);
  }

  if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
  {
    mCamera->set_distance(0.1);
  }

  // Left mouse button pressed
  int left_mouse = glfwGetMouseButton(mWindow, 0);
  int right_mouse = glfwGetMouseButton(mWindow, 1);
  
  double x, y;
  glfwGetCursorPos(mWindow, &x, &y);

  mCamera->on_mouse_move(x, y, left_mouse == GLFW_PRESS, right_mouse == GLFW_PRESS);
  
}

bool JGLWindow::load_mesh()
{
  mMesh = std::make_unique<Mesh>();

  ObjMeshImporter objImporter;
  if (!objImporter.from_file(mModel, mMesh.get()))
  {
    fprintf(stderr, "Error: Model cant be loaded\n");
    return false;
  }

  mMesh->init();
  return true;
}
