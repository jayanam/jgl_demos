#pragma once

#include "render_base.h"

namespace nrender
{
  class UIContext : public RenderContext
  {

  public:

    void init(GLFWwindow* window) override;

    void render() override;

    void end() override;

  private:
    float mPosx = 0;
  };
}
