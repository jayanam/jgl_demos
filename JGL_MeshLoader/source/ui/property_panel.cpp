#include "pch.h"
#include "property_panel.h"

#include "imgui.h"
#include "utils/imgui_widgets.h"

namespace nui
{
  void Property_Panel::render(nui::SceneView* scene_view)
  {
    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Light"))
    {
      ImGui::ColorPicker3("Color", (float*)&scene_view->get_light()->mColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
    
      ImGui::Separator();
      ImGui::Text("Position");
      ImGui::Separator();
      nimgui::draw_vec3_widget("Position", scene_view->get_light()->mPosition, 80.0f);
    }

    ImGui::End();
  }
}
