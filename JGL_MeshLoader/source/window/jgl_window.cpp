#include "pch.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "jgl_window.h"
#include "elems/input.h"

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

  mWidth = width;
  mHeight = height;

  /* Initialize the library */
  if (!glfwInit())
  {
    fprintf(stderr, "Error: GLFW Window couldn't be initialized\n");
    mIsValid = false;
  }

  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 410";

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
  
  glfwSwapInterval(1); // Enable vsync

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    mIsValid = false;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

  ImGui::StyleColorsDark();

  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  glEnable(GL_DEPTH_TEST);

  auto aspect = (float)width / (float)height;
  mShader = std::make_unique<Shader>();
  mShader->load("shaders/vs.shader", "shaders/fs.shader");

  mCamera = std::make_unique<Camera>(glm::vec3(0, 0, 3), 45.0f, aspect, 0.1f, 100.0f);

  mLight = std::make_unique<Light>(0.0f, 0.4f, 1.0f, 1.0f);


  return mIsValid;
}

JGLWindow::~JGLWindow()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

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
  mWidth = width;
  mHeight = height;

  mCamera->set_aspect((float)width / (float)height);
  glViewport(0, 0, width, height);
}

void JGLWindow::on_key(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
  }
}

void JGLWindow::render()
{
  load_mesh();

  mShader->use();

  glm::vec4 vColor{ 0.7f, 0.1f, 0.1f, 1.0f };
  mShader->set_vec4(vColor, "color");

  bool show_demo_window = false;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(mWindow))
  {
    glViewport(0, 0, mWidth, mHeight);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShader->update_camera(mCamera.get());

    mShader->update_light(mLight.get());


    if (mMesh)
    {
      mMesh->draw_faces();
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /// *************************
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoBackground;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags); 
    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::Begin("Stats");
    ImGui::Text("Renderer2D Stats:");
    ImGui::End();

    ImGui::End();
    /// *************************
   
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)mWidth, (float)mHeight);

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    handle_input();

    glfwPollEvents();

    glfwSwapBuffers(mWindow);

  }

  mShader->unload();
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
      vh.mPos    = { mesh->mVertices[i].x, mesh->mVertices[i].y ,mesh->mVertices[i].z };
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
