#pragma once

#include "elems/light.h"
#include "ui/scene_view.h"

#include "imgui.h"
#include "utils/imgui_widgets.h"
#include <ImFileBrowser.h>

namespace nui
{
  class Property_Panel
  {
  public:

    Property_Panel()
    {
      mCurrentFile = "< ... >";

      mFileDialog.SetTitle("Open mesh");
      mFileDialog.SetFileFilters({ ".fbx", ".obj" });
    }

    void render(nui::SceneView* mScene);

    void set_mesh_load_callback(const std::function<void(const std::string&)>& callback)
    {
      mMeshLoadCallback = callback;
    }

  private:
    // create a file browser instance
    ImGui::FileBrowser mFileDialog;

    std::function<void(const std::string&)> mMeshLoadCallback;

    std::string mCurrentFile;


  };
}

