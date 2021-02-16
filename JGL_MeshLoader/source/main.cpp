#include "pch.h"
#include "main.h"
#include "window/jgl_window.h"

int main(void)
{
  JGLWindow glWindow;
  if (glWindow.init(800, 600, "JMesh Loader: Open GL Demo"))
  {
    glWindow.render();
  }

  return 0;
}
