#include "pch.h"
#include "jgl_window.h"

// Global window callbacks
static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  JGLWindow* pWindow = static_cast<JGLWindow*>(glfwGetWindowUserPointer(window));
  pWindow->on_key(key, scancode, action, mods);
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
  glfwMakeContextCurrent(mWindow);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    mIsValid = false;
  }

  auto aspect = (float)width / (float)height;
  mShader = std::make_unique<ShaderUtil>();
  mCamera = std::make_unique<Camera>(glm::vec3(0, 0, -3), 45.0f, aspect, 0.1f, 100.0f);

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

void JGLWindow::on_key(int key, int scancode, int action, int mods)
{
  // Toggle draw faces
  if (key == GLFW_KEY_F && action == GLFW_PRESS)
  {
    mDrawFlags.draw_faces = !mDrawFlags.draw_faces;
  }

  // Toggle draw edges
  if (key == GLFW_KEY_E && action == GLFW_PRESS)
  {
    mDrawFlags.draw_edges = !mDrawFlags.draw_edges;
  }
}

void JGLWindow::render()
{
  mShader->load("shaders/vs.shader", "shaders/fs.shader");

  std::unique_ptr<Mesh> pMesh = std::make_unique<Mesh>();

  ObjMeshImporter objImporter;
  if (!objImporter.from_file("model.obj", pMesh.get()))
  {
    fprintf(stderr, "Error: Model cant be loaded\n");
    return;
  }

  glEnable(GL_DEPTH_TEST);

  pMesh->init();

  glm::mat4 model{ 1.0f };

  mShader->use();

  // Get all uniform locations for shader
  GLint modelLoc = glGetUniformLocation(mShader->get_program_id(), "model");
  GLint viewLoc = glGetUniformLocation(mShader->get_program_id(), "view");
  GLint projLoc = glGetUniformLocation(mShader->get_program_id(), "projection");

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mCamera->get_view()));
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mCamera->get_perspective()));

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(mWindow))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the mesh
    if (mDrawFlags.draw_faces)
    {
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.0f, 1.0f);

      glm::vec4 vColor{ 0.7f, 0.1f, 0.1f, 1.0f };
      mShader->set_vec4(vColor, "color");
      pMesh->draw_faces();
      glDisable(GL_POLYGON_OFFSET_FILL);
    }

    if (mDrawFlags.draw_edges)
    {
      glm::vec4 vColor{ 1.0f, 1.0f, 1.0f, 1.0f };
      mShader->set_vec4(vColor, "color");
      pMesh->draw_wireframe();
    }

    glfwSwapBuffers(mWindow);

    glfwPollEvents();
  }

  mShader->unload();
}




