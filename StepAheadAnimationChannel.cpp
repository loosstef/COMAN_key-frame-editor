//
// Created by stef on 06.04.20.
//

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include "StepAheadAnimationChannel.h"
#include "Object.h"
#include "Path.h"
#include "Keyframe.h"

void StepAheadAnimationChannel::render(int frameIndex, GLint uniformLocTransMat) {
    for(Object *object : mObjects) {
        if(mPath == nullptr) {
            object->draw(uniformLocTransMat);
        }
        else {
//            Keyframe keyframe = mPath->getKeyframe_DEPRECATED(frameIndex);
            Orientation orientation = mPath->orientation(frameIndex);
//            glm::vec3 rot = orientation.rotation;
//            glm::mat4 rotMat = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);
            glm::mat4 rotMat = glm::toMat4(orientation.rotation);
            glm::mat4 transMat = glm::translate(glm::mat4(1.0f), orientation.position);

            glm::mat4 transformationMatrix = glm::scale(transMat*rotMat, orientation.scale);

//            glm::mat4 transformationMatrix = transMat * rotMat * scaleMat;
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
