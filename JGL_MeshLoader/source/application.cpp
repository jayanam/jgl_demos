#include "pch.h"

#include "application.h"

#include "window/jgl_window.h"

Application::Application(const std::string& app_name)
{
  mWindow = std::make_unique<JGLWindow>();
  mWindow->init(800, 600, app_name);
}

void Application::loop()
{
  while (mWindow->is_running())
  {
    mWindow->render();
  }
}