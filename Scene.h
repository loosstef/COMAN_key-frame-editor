//
// Created by stef on 21.04.20.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H


#include "RenderEngine.h"
#include "Clock.h"

class Scene {
public:
    RenderEngine* getRenderEngine() { return renderEngine; }
    void setRenderEngine(RenderEngine *re) { renderEngine = re; }
    Clock* getClock() { return clock; }
    void setClock(Clock *c) { clock = c; }
    std::vector<StepAheadAnimationChannel*>& getSaaChannels() { return saaChannels; }
    void addSaaChannel(StepAheadAnimationChannel *saaChannel);
private:
    RenderEngine *renderEngine;
    Clock *clock;
    std::vector<StepAheadAnimationChannel*> saaChannels;
};


#endif //PROJECT_SCENE_H
