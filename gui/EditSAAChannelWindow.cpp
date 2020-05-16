//
// Created by stef on 08.04.20.
//

#include "EditSAAChannelWindow.h"
#include <string.h>
#include <iostream>
#include "../vendor/imgui/imgui.h"
#include "../Path.h"
#include "../Keyframe.h"
#include "../FFD.h"

EditSAAChannelWindow::EditSAAChannelWindow(Clock *clock) : sceneClock(clock) {

}

void EditSAAChannelWindow::Render(StepAheadAnimationChannel *saaChannel) {
//    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Always);
    ImGui::SetNextWindowSizeConstraints(ImVec2(316, 300), ImVec2(316, FLT_MAX));
    ImGuiWindowFlags window_flags = 0;
//    window_flags |= ImGuiWindowFlags_NoResize;
//    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::Begin("Edit StepAheadAnimationChannel", NULL, window_flags);
    std::list<Keyframe>* keyframes = saaChannel->getPath()->getKeyFrames();
    ImGui::Text("Object stats:");
    Orientation currOrient = saaChannel->getPath()->orientation(sceneClock->getFrameIndex());
    ImGui::DragFloat3("position", &currOrient.position[0], 0.02f, 0, 0, "%0.3f", ImGuiInputTextFlags_ReadOnly);
    ImGui::DragFloat4("rotation", &currOrient.rotation[0], 0.02f, 0, 0, "%0.3f", ImGuiInputTextFlags_ReadOnly);
    ImGui::DragFloat3("scale", &currOrient.scale[0], 0.02f, 0, 0, "%0.3f", ImGuiInputTextFlags_ReadOnly);
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("EditSaaChannelTabBar_1", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Keyframes")) {
            showKeyframes(saaChannel);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("FFD")) {
            showFFDs(saaChannel);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void EditSAAChannelWindow::showKeyframes(StepAheadAnimationChannel *saaChannel) {
    std::list<Keyframe>* keyframes = saaChannel->getPath()->getKeyFrames();
    int i = 0;
    for(auto &keyframe : *keyframes) {
        std::string menuLabel = std::string("keyframe ") + std::to_string(i);
        ImGui::BeginChild(menuLabel.data(), ImVec2(300, 110), true);
        ImGui::DragInt("frame", &keyframe.getFrameIndex());
        ImGui::DragFloat3("location", &keyframe.getPos()[0], 0.02f);
        ImGui::DragFloat3("rotation", &keyframe.getRot()[0], 0.005f);
        ImGui::DragFloat3("Scale", &keyframe.getScale()[0], 0.005f);
        ImGui::EndChild();
        ++i;
    }
    if(ImGui::Button("Add keyframe")) {
        saaChannel->getPath()->addKeyframe(Keyframe(sceneClock->getFrameIndex()));
    }
}

void EditSAAChannelWindow::showFFDs(StepAheadAnimationChannel *saaChannel) {
    std::vector<int>& frameIndices = saaChannel->getFFDIndices();
    for(int index : frameIndices) {
        std::string menuLabel = std::string("ffd ") + std::to_string(index);
        ImGui::BeginChild(menuLabel.data(), ImVec2(300, 60), true);
        std::string frameText = std::to_string(index);
        ImGui::Text(frameText.data());
//        if(ImGui::Button("Jump here")) {
//
//        }
//        ImGui::SameLine();
        if(ImGui::Button("Remove")) {
            saaChannel->removeFFD(index);
        }
        ImGui::EndChild();
//        std::string menuLabel = std::string("ffd ") + std::to_string(i);
//        ImGui::BeginChild(menuLabel.data(), ImVec2(300, 110), true);
//        ImGui::DragInt("frame", &keyframe.getFrameIndex());
//        ImGui::DragFloat3("location", &keyframe.getPos()[0], 0.02f);
//        ImGui::DragFloat3("rotation", &keyframe.getRot()[0], 0.005f);
//        ImGui::DragFloat3("Scale", &keyframe.getScale()[0], 0.005f);
//        ImGui::EndChild();
    }
    if(ImGui::Button("Add FFD")) {
        ImGui::OpenPopup("add new FFD");
    }

    // MODAL
    if (ImGui::BeginPopupModal("add new FFD", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::DragInt("frame index", &field_new_ffd_frame_index);
        ImGui::DragInt3("dimensions", &field_new_ffd_dimensions[0]);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            field_new_ffd_frame_index = 0;
            field_new_ffd_dimensions = glm::tvec3<int>(2);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // add btn
        if (ImGui::Button("Add")) {
            int frameIndex = field_new_ffd_frame_index;
            int s = field_new_ffd_dimensions.x;
            int t = field_new_ffd_dimensions.y;
            int u = field_new_ffd_dimensions.z;
            saaChannel->addFFD(frameIndex, new FFD(*saaChannel->getModel(), s, t, u));
            field_new_ffd_frame_index = 0;
            field_new_ffd_dimensions = glm::tvec3<int>(2);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}
