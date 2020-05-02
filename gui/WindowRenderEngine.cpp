//
// Created by stef on 07.04.20.
//

#include "WindowRenderEngine.h"
#include "../Channel.h"
#include "../StepAheadAnimationChannel.h"

WindowRenderEngine::WindowRenderEngine(Clock *clock) :
    timelineWindow(clock),
    editSaaChannelWindow(clock)
{

}

void WindowRenderEngine::render(Picked picked) {
    Channel * pickedChannel = picked.channel;
    CJoint *pickedJoint = picked.joint;
    timelineWindow.render();
    if(pickedChannel != nullptr) {
        if(pickedChannel->getType() == SAA) {
            editSaaChannelWindow.Render((StepAheadAnimationChannel*)pickedChannel);
        }
    }
    if(pickedJoint != nullptr) {
        editJointWindow.Render(pickedJoint);
    }
}
