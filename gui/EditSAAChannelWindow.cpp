//
// Created by stef on 08.04.20.
//

#include "EditSAAChannelWindow.h"
#include <string.h>
#include <iostream>
#include "../vendor/imgui/imgui.h"
#include "../Path.h"
#include "../Keyframe.h"

EditSAAChannelWindow::EditSAAChannelWindow(Clock *clock) : sceneClock(clock) {

}

void EditSAAChannelWindow::Render(StepAheadAnimationChannel *saaChannel) {
    ImGui::Begin("Edit StepAheadAnimationChannel", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    std::list<Keyframe>* keyframes = saaChannel->getPath()->getKeyFrames();
    ImGui::Text("Object stats:");
    Orientation currOrient = saaChannel->getPath()->orientation(sceneClock->getFrameIndex());
    ImGui::DragFloat3("position", &currOrient.position[0], 0.02f, 0, 0, "%0.3f", ImGuiInputTextFlags_ReadOnly);
    ImGui::DragFloat4("rotation", &currOrient.rotation[0], 0.02f, 0, 0, "%0.3f", ImGuiInputTextFlags_ReadOnly);
    ImGui::DragFloat3("scale", &currOrient.scale[0], 0.02f, 0, 0, "%0.3f", ImGuiInputTextFlags_ReadOnly);
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
    for(int i = 0; i < keyframes->size(); ++i) {
    }
    ImGui::End();
}
