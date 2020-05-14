//
// Created by stef on 21.04.20.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H


#include "RenderEngine.h"
#include "Clock.h"
#include "Plant.h"

class CSkeleton;
class SkyBox;

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
    void add(Plant *plant);
    std::vector<Plant*>& getPlants() { return plants; }
    void setSkyBox(std::vector<std::string> &faces);
    SkyBox *getSkyBox() { return skyBox; }
private:
    RenderEngine *renderEngine = nullptr;
    Clock *clock;
    std::vector<StepAheadAnimationChannel*> saaChannels;
    std::vector<CSkeleton*> skeletons;
    std::vector<Plant*> plants;
    SkyBox *skyBox = nullptr;
};


#endif //PROJECT_SCENE_H
