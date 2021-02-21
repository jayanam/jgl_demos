#include "pch.h"
#include "property_panel.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace nui
{
  void Property_Panel::render(nui::SceneView* scene_view)
  {
    ImGui::Begin("Properties");
    ImGui::Text("Light:");

    ImGui::ColorPicker3("Color", (float*)&scene_view->get_light()->mColor, ImGuiColorEditFlags_PickerHueWheel);

    ImGui::End();
  }
}
