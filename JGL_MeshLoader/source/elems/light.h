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

    glm::vec3 get_color() const { return mColor; }

    glm::vec3 get_position() const { return mPosition; }

    float get_strength() const { return mStrength; }

    glm::vec3 mPosition = { 0.0f, 0.5f, 2.0f };

  private:
    glm::vec3 mColor = { 1.0f, 1.0f, 1.0f };

    float mStrength = 1.0f;

  };
}