//
// Created by stef on 06.04.20.
//

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include "StepAheadAnimationChannel.h"
#include "Object_DEPRECATED.h"
#include "Path.h"
#include "Keyframe.h"


void StepAheadAnimationChannel::setPath(Path *path) {
    mPath = path;
}


void StepAheadAnimationChannel::addObject_DEPRECATED(Object_DEPRECATED *object) {
    mObject = object;
//    mObjects.push_back(object);
}