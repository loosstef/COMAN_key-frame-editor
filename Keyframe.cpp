//
// Created by stef on 10.04.20.
//

#include "Keyframe.h"

Keyframe::Keyframe(int frameIndex, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) :
    mFrameIndex(frameIndex), mPos(pos), mRot(rot), mScale(scale)
{
}
