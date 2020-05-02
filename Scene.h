//
// Created by stef on 21.04.20.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H


#include "RenderEngine.h"
#include "Clock.h"

class CSkeleton;

class Scene {
public:
    RenderEngine& getRenderEngine() { return *renderEngine; }
    void setRenderEngine(RenderEngine *re) { renderEngine = re; }
    Clock* getClock() { return clock; }
    void setClock(Clock *c) { clock = c; }
    std::vector<StepAheadAnimationChannel*>& getSaaChannels() { return saaChannels; }
    void addSaaChannel(StepAheadAnimationChannel *saaChannel);
    std::vector<CSkeleton*>& getSkeletons() { return skeletons; }
    void addSkeleton(CSkeleton *skeleton);
private:
    RenderEngine *renderEngine = nullptr;
    Clock *clock;
    std::vector<StepAheadAnimationChannel*> saaChannels;
    std::vector<CSkeleton*> skeletons;
};


#endif //PROJECT_SCENE_H
