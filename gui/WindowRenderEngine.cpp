//
// Created by stef on 07.04.20.
//

#include "WindowRenderEngine.h"

WindowRenderEngine::WindowRenderEngine(Clock *clock) :
    timelineWindow(clock)
{

}

void WindowRenderEngine::render() {
    timelineWindow.render();
}
