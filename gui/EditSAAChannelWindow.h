//
// Created by stef on 08.04.20.
//

#ifndef PROJECT_EDITSAACHANNELWINDOW_H
#define PROJECT_EDITSAACHANNELWINDOW_H


#include "../StepAheadAnimationChannel.h"
#include "../Clock.h"

class EditSAAChannelWindow {
public:
    EditSAAChannelWindow(Clock *clock);
    void Render(StepAheadAnimationChannel *saaChannel);
private:
    Clock *sceneClock;
};


#endif //PROJECT_EDITSAACHANNELWINDOW_H
