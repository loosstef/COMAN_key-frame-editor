//
// Created by stef on 21.04.20.
//

#include "Scene.h"
#include "SkyBox.h"

void Scene::addSaaChannel(StepAheadAnimationChannel *saaChannel) {
    saaChannels.push_back(saaChannel);
//    renderEngine->addSaaChannel(saaChannel);
}

void Scene::addSkeleton(CSkeleton *skeleton) {
    skeletons.push_back(skeleton);
}

void Scene::add(Plant *plant) {
    plants.push_back(plant);
}

void Scene::setSkyBox(std::vector<std::string> &faces) {
    if(skyBox != nullptr) {
        delete skyBox;
    }
    skyBox = new SkyBox(faces);
}
