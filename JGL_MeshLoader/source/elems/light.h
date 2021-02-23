#pragma once

#include "pch.h"

#include "element.h"
#include "shader/shader_util.h"

namespace nelems
{
  class Light : public Element
  {
  public:

    Light()
    {
      mColor = glm::vec3(1.0, 1.0f, 10.0f);
      mStrength = 100.0f;
    }

    ~Light() {}

    void update(nshaders::Shader* shader) override
    {

      shader->set_vec3(mPosition, "lightPosition");
      shader->set_vec3(mColor * mStrength, "lightColor");
      
    }

    glm::vec3 mPosition = { 1.5f, 3.5f, 3.0f };

    glm::vec3 mColor = { 1.0f, 1.0f, 1.0f };

    float mStrength = 100.0f;

  };
}