//
// Created by stef on 21.04.20.
//

#include "Scene.h"

void Scene::addSaaChannel(StepAheadAnimationChannel *saaChannel) {
    saaChannels.push_back(saaChannel);
    renderEngine->addSaaChannel(saaChannel);
}