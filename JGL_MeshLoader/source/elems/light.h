#pragma once

#include "pch.h"

namespace nelems
{
  class Light
  {
  public:

    Light()
    {
      mColor = glm::vec3(1.0f, 1.0f, 1.0f);
      mStrength = 1.0f;
    }

    ~Light() {}

    glm::vec3 mPosition = { 1.5f, 3.5f, 3.0f };

    glm::vec3 mColor = { 1.0f, 1.0f, 1.0f };

    float mStrength = 1.0f;

  };
}