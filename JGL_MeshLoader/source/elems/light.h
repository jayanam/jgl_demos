#pragma once

#include "pch.h"

namespace nelems
{
  class Light
  {
  public:
    Light() : Light(1.0f, 1.0f, 1.0f, 1.0f)
    {
    }

    Light(float r, float g, float b, float strength)
    {
      mColor = glm::vec3(r, g, b);
      mStrength = strength;
    }

    ~Light() {}

    glm::vec3 mPosition = { 2.0f, 1.5f, 3.0f };

    glm::vec3 mColor = { 1.0f, 1.0f, 1.0f };

    float mStrength = 1.0f;

  };
}