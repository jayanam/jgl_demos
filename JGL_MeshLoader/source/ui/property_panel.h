#pragma once

#include "elems/light.h"

namespace nui
{
  class UI_Property_Panel
  {
  public:
    UI_Property_Panel(nelems::Light* light) :
      mLight(light)
    {}

    void render();

  private:
    nelems::Light* mLight;
  };
}

