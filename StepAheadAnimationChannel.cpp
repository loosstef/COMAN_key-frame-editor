//
// Created by stef on 06.04.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include "StepAheadAnimationChannel.h"
#include "Object.h"
#include "Path.h"

void StepAheadAnimationChannel::render(int frameIndex, GLint uniformLocTransMat) {
    for(Object *object : mObjects) {
        if(mPath == nullptr) {
            object->draw(uniformLocTransMat);
        }
        else {
            Keyframe keyframe = mPath->getKeyframe(frameIndex);
            glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), keyframe.pos);
            object->draw(uniformLocTransMat, transformationMatrix);
        }
    }
}

void StepAheadAnimationChannel::addObject(Object *object) {
    mObjects.push_back(object);
}

void StepAheadAnimationChannel::setPath(Path *path) {
    mPath = path;
}

Object *StepAheadAnimationChannel::getObject(int index) {
    return mObjects[index];
}
