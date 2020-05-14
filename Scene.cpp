//
// Created by stef on 21.04.20.
//

#include "Scene.h"
#include "SkyBox.h"

void Scene::init(RenderEngine *re, Clock *clock) {
    mRenderEngine = re;
    mClock = clock;
}

Scene::~Scene() {
    delete mRenderEngine;
    delete mClock;
    delete mSkyBox;
}

void Scene::add(StepAheadAnimationChannel *saaChannel) {
    mSaaChannels.push_back(saaChannel);
//    renderEngine->add(saaChannel);
}

void Scene::add(CSkeleton *skeleton) {
    mSkeletons.push_back(skeleton);
}

void Scene::add(Plant *plant) {
    mPlants.push_back(plant);
}

void Scene::add(Camera *camera) {
    mCameras.push_back(camera);
}

void Scene::setSkyBox(std::vector<std::string> &faces) {
    if(mSkyBox != nullptr) {
        delete mSkyBox;
    }
    mSkyBox = new SkyBox(faces);
}
