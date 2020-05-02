//
// Created by stef on 02.05.20.
//

#include "EditJointWindow.h"
#include "../vendor/imgui/imgui.h"
#include "../CJoint.h"

void EditJointWindow::Render(CJoint *joint) {
    const int windowWidth = 360;
    const int minWindowHeight = 100;
    ImGuiWindowFlags window_flags = 0;
    ImGui::SetNextWindowSizeConstraints(ImVec2(windowWidth, minWindowHeight), ImVec2(windowWidth, FLT_MAX));
    ImGui::Begin("Edit Joint", NULL, window_flags);
//    ImGui::DragFloat("link offset", joint->ImGui_linkOffset(), 0.01f);
    ImGui::DragFloat("joint angle", joint->ImGui_jointAngle(), 0.01f, *joint->ImGui_minJointAngle(), *joint->ImGui_maxJointAngle());
    ImGui::DragFloat("min joint angle", joint->ImGui_minJointAngle(), 0.01f);
    ImGui::DragFloat("max joint angle", joint->ImGui_maxJointAngle(), 0.01f);
    ImGui::End();
}
