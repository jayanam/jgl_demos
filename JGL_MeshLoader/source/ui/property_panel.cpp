#include "pch.h"
#include "property_panel.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace nui
{
  void UI_Property_Panel::render()
  {
    ImGui::Begin("Properties");
    ImGui::Text("Light:");

    ImGui::ColorEdit4("Color", (float*)&mLight->mColor);
    ImGui::End();
  }
}
