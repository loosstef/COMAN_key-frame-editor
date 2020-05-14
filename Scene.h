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
    // destructor
    ~Scene();
    // init function
    void init(RenderEngine *re = new RenderEngine(), Clock *clock = new Clock());
    // setters
    void setSkyBox(std::vector<std::string> &faces);
    // getters
    RenderEngine& renderEngine() { return *mRenderEngine; }
    Clock* clock() { return mClock; }
    std::vector<StepAheadAnimationChannel*>& saaChannels() { return mSaaChannels; }
    std::vector<CSkeleton*>& skeletons() { return mSkeletons; }
    std::vector<Plant*>& plants() { return mPlants; }
    SkyBox *skyBox() { return mSkyBox; }
    std::vector<Camera*>& cameras() { return mCameras; }
    // add scene objects
    void add(StepAheadAnimationChannel *saaChannel);
    void add(CSkeleton *skeleton);
    void add(Plant *plant);
    void add(Camera *camera);
private:
    RenderEngine *mRenderEngine = nullptr;
    Clock *mClock = nullptr;
    std::vector<StepAheadAnimationChannel*> mSaaChannels;
    std::vector<CSkeleton*> mSkeletons;
    std::vector<Plant*> mPlants;
    SkyBox *mSkyBox = nullptr;
    std::vector<Camera*> mCameras;
};


#endif //PROJECT_SCENE_H
