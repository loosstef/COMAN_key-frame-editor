//
// Created by stef on 18.05.20.
//

#include "RenderEngineWindow.h"
#include "../Scene.h"
#include "../vendor/imgui/imgui.h"
#include "../RenderEngine.h"
#include "../Camera.h"


RenderEngineWindow::RenderEngineWindow(Scene &scene) : mScene(scene) {
}

void RenderEngineWindow::render() {
    ImGui::SetNextWindowSizeConstraints(ImVec2(316, 100), ImVec2(316, FLT_MAX));
    ImGuiWindowFlags window_flags = 0;
    ImGui::Begin("Render Engine", NULL, window_flags);
    // camera dropdown
    static int current_idx = 0;
    Camera &editorCamera = mScene.renderEngine().editorCamera();
    Camera &currCamera = mScene.renderEngine().camera();
    if (ImGui::BeginCombo("camera", currCamera.name().c_str(), 0))
    {
        const bool currCamIsSelected = (editorCamera.name().compare(currCamera.name()) == 0);
        if(ImGui::Selectable(editorCamera.name().c_str(), currCamIsSelected)) {
            mScene.renderEngine().useCamera(editorCamera);
        }
        if(currCamIsSelected)
            ImGui::SetItemDefaultFocus();

        for(auto *camera : mScene.cameras()) {
            const bool isSelected = (camera->name().compare(currCamera.name()) == 0);
            if(ImGui::Selectable(camera->name().c_str(), isSelected)) {
                mScene.renderEngine().useCamera(*camera);
            }
            if(isSelected)
                ImGui::SetItemDefaultFocus();
        }

//        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
//        {
//            const bool is_selected = (item_current_idx == n);
//            if (ImGui::Selectable(items[n], is_selected))
//                item_current_idx = n;
//
//            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
//            if (is_selected)
//                ImGui::SetItemDefaultFocus();
//        }
//        ImGui::EndCombo();
        ImGui::EndCombo();
    }
    ImGui::End();
}
