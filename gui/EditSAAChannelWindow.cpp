//
// Created by stef on 08.04.20.
//

#include "EditSAAChannelWindow.h"
#include <string.h>
#include <iostream>
#include "../vendor/imgui/imgui.h"
#include "../Path.h"

void EditSAAChannelWindow::Render(StepAheadAnimationChannel *saaChannel) {
    ImGui::Begin("Edit StepAheadAnimationChannel", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    std::list<Keyframe>* keyframes = saaChannel->getPath()->getKeyFrames();
    int i = 0;
    for(auto &keyframe : *keyframes) {
        std::string menuLabel = std::string("keyframe ") + std::to_string(i);
        ImGui::BeginChild(menuLabel.data(), ImVec2(300, 80), true);
        std::string framePickerLabel = std::string("frame#") + std::to_string(i);
        ImGui::DragInt("frame", &keyframe.frameIndex);
        std::string keyframeLocLabel = std::string("location#") + std::to_string(i);
        ImGui::DragFloat3("location", &keyframe.pos[0], 0.02f);
        ImGui::EndChild();
        ++i;
    }
    for(int i = 0; i < keyframes->size(); ++i) {
    }
    ImGui::End();
}
