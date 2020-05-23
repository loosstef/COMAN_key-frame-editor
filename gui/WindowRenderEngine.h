//
// Created by stef on 07.04.20.
//

#ifndef PROJECT_WINDOWRENDERENGINE_H
#define PROJECT_WINDOWRENDERENGINE_H

#include "TimelineWindow.h"
#include "EditSAAChannelWindow.h"
#include "../Picked.h"
#include "EditJointWindow.h"
#include "RenderEngineWindow.h"
#include "MainMenuBar.h"

class Clock;
class Channel;
class Scene;

class WindowRenderEngine {
public:
    WindowRenderEngine(Scene &scene);
    void render(Picked picked);
    bool showTimeLineWindow = true;
    bool showRenderEngineWindow = true;
private:
    TimelineWindow timelineWindow;
    EditSAAChannelWindow editSaaChannelWindow;
    EditJointWindow editJointWindow;
    RenderEngineWindow renderEngineWindow;
    MainMenuBar mainMenuBar;
};


#endif //PROJECT_WINDOWRENDERENGINE_H
