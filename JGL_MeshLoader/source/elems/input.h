#pragma once

#include "pch.h"

namespace nelems
{
  enum class EInputButton
  {
    Left = 0,
    Right = 1,
    Middle = 2,
    None = 9
  };

  class Input
  {
  public:
    static EInputButton GetPressedButton(GLFWwindow* window)
    {
      EInputButton result = EInputButton::None;

      if (glfwGetMouseButton(window, 0) == GLFW_PRESS)
        return EInputButton::Left;
      else if (glfwGetMouseButton(window, 1) == GLFW_PRESS)
        return EInputButton::Right;
      else if (glfwGetMouseButton(window, 2) == GLFW_PRESS)
        return EInputButton::Middle;
      
      return EInputButton::None;

    }
  };
}
