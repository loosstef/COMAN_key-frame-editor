//
// Created by stef on 07.04.20.
//

#include "WindowRenderEngine.h"
#include "../Channel.h"
#include "../StepAheadAnimationChannel.h"
#include "../Scene.h"

WindowRenderEngine::WindowRenderEngine(Scene &scene) :
    timelineWindow(scene.clock()),
    editSaaChannelWindow(scene.clock()),
    renderEngineWindow(scene),
    mainMenuBar(scene, *this)
{

}

void WindowRenderEngine::render(Picked picked) {
    Channel * pickedChannel = picked.channel;
    CJoint *pickedJoint = picked.joint;
    mainMenuBar.render();
    if(showRenderEngineWindow) {
        renderEngineWindow.render();
    }
    if(showTimeLineWindow) {
        timelineWindow.render();
    }
    if(pickedChannel != nullptr) {
        if(pickedChannel->getType() == SAA) {
            editSaaChannelWindow.Render((StepAheadAnimationChannel*)pickedChannel);
        }
    }
    if(pickedJoint != nullptr) {
        editJointWindow.Render(pickedJoint);
    }
}
