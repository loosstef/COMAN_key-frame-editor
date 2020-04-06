//
// Created by stef on 06.04.20.
//

#include "StepAheadAnimationChannel.h"
#include "Object.h"

void StepAheadAnimationChannel::render(int frameIndex, GLint uniformLocTransMat) {
    for(Object *object : mObjects) {
        if(mPath == nullptr) {
            object->draw(uniformLocTransMat);
        }
    }
    // TODO: add render code
}

void StepAheadAnimationChannel::addObject(Object *object) {
    mObjects.push_back(object);
}
