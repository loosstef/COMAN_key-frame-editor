//
// Created by stef on 07.04.20.
//

#ifndef PROJECT_WINDOWRENDERENGINE_H
#define PROJECT_WINDOWRENDERENGINE_H

#include "TimelineWindow.h"
#include "EditSAAChannelWindow.h"

class Clock;
class Channel;

class WindowRenderEngine {
public:
    WindowRenderEngine(Clock *clock);
    void render(Channel *pickedChannel);
private:
    TimelineWindow timelineWindow;
    EditSAAChannelWindow editSaaChannelWindow;
};


#endif //PROJECT_WINDOWRENDERENGINE_H
