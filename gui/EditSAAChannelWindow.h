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
    void showKeyframes(StepAheadAnimationChannel *saaChannel);
    void showFFDs(StepAheadAnimationChannel *saaChannel);
    Clock *sceneClock;
    int field_new_ffd_frame_index = 0;
    glm::tvec3<int> field_new_ffd_dimensions = glm::tvec3<int>(2);
};


#endif //PROJECT_EDITSAACHANNELWINDOW_H
