#pragma once

#include "pch.h"

#include "window/jgl_window.h"



class Application
{

public:
  Application(std::string& app_name);

  static Application& Instance() { return *s_Instance; }
private:
  static Application* s_Instance;

  std::unique_ptr<JGLWindow> mWindow;
};
