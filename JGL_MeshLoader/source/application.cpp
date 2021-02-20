#include "pch.h"

#include "application.h"

Application::Application(std::string& app_name)
{
  mWindow = std::make_unique<JGLWindow>();
  mWindow->init(800, 600, app_name);

  mWindow->render();
}