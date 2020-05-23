//
// Created by stef on 07.04.20.
//

#include "TimelineWindow.h"
#include "../vendor/imgui/imgui.h"
#include "../Clock.h"

TimelineWindow::TimelineWindow(Clock *clock) :
    mClock(clock)
{

}

void TimelineWindow::render() {
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Always);
    ImGui::Begin("Timeline", NULL, window_flags);
        if(mClock->isRunning()) {
            if(ImGui::Button("Pause"))
                mClock->pause();
        }
        else {
            if(ImGui::Button("Start"))
                mClock->start();
        }
    ImGui::SetNextItemWidth(600);
        ImGui::SliderInt("frame", mClock->imGui_frameIndex(), 0, *mClock->imGui_lastFrameIndex());
        if(ImGui::TreeNode("Advanced Settings")) {
            ImGui::SetNextItemWidth(150);
            ImGui::DragInt("fps", mClock->imGui_fps(), 0.2f, 1, 60);
            ImGui::SetNextItemWidth(150);
            ImGui::InputInt("last frame", mClock->imGui_lastFrameIndex());
            ImGui::TreePop();
        }
    ImGui::End();
}
