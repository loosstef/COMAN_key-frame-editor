//
// Created by stef on 07.04.20.
//

#ifndef PROJECT_WINDOWRENDERENGINE_H
#define PROJECT_WINDOWRENDERENGINE_H

#include "TimelineWindow.h"

class Clock;

class WindowRenderEngine {
public:
    WindowRenderEngine(Clock *clock);
    void render();
private:
    TimelineWindow timelineWindow;
};


#endif //PROJECT_WINDOWRENDERENGINE_H
