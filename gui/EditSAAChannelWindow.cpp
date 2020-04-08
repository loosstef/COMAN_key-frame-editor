//
// Created by stef on 08.04.20.
//

#include "EditSAAChannelWindow.h"
#include "../vendor/imgui/imgui.h"

void EditSAAChannelWindow::Render(StepAheadAnimationChannel *saaChannel) {
    ImGui::Begin("Edit StepAheadAnimationChannel", NULL);
        ImGui::Text("Hello world");
    ImGui::End();
}
