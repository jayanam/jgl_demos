#pragma once

#include "window/jgl_window.h"
#include "elems/camera.h"

class Application
{

public:
  Application(const std::string& app_name);

  static Application& Instance() { return *sInstance; }

  void loop();

private:
  static Application* sInstance;

  std::unique_ptr<nwindow::GLWindow> mWindow;
};
