//
// Created by stef on 07.04.20.
//

#include "WindowRenderEngine.h"
#include "../Channel.h"
#include "../StepAheadAnimationChannel.h"

WindowRenderEngine::WindowRenderEngine(Clock *clock) :
    timelineWindow(clock)
{

}

void WindowRenderEngine::render(Channel *pickedChannel) {
    timelineWindow.render();
    if(pickedChannel != nullptr) {
        if(pickedChannel->getType() == SAA) {
            editSaaChannelWindow.Render((StepAheadAnimationChannel*)pickedChannel);
        }
    }
}
