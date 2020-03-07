#include "pch.h"
#include "main.h"
#include "jgl_window.h"

int main(void)
{
  JGLWindow glWindow;
  if (glWindow.init(640, 480, "JMesh Loader: Open GL Demo"))
  {
    glWindow.render();
  }

  return 0;
}
