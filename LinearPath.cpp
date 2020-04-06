//
// Created by stef on 06.04.20.
//

#include "LinearPath.h"


void LinearPath::addKeyframe(Keyframe newKeyframe) {
    for(auto it = mKeyframes.begin(); it != mKeyframes.end(); it++) {
        if(it->frameIndex == newKeyframe.frameIndex) {
            it->pos = newKeyframe.pos;
            return;
        }
        else if(it->frameIndex > newKeyframe.frameIndex) {
            mKeyframes.insert(it, newKeyframe);
            return;
        }
    }
    mKeyframes.push_back(newKeyframe);
}


bool LinearPath::hasKeyframe(uint frameIndex) {
    for(Keyframe keyframe : mKeyframes) {
        if(keyframe.frameIndex == frameIndex)
            return true;
        else if(keyframe.frameIndex > frameIndex)
            return false;
    }
    return false;
}


Keyframe LinearPath::getKeyframe(uint frameIndex) {
    // if no keyframes set yet. Position must be in origin.
    if(mKeyframes.size() == 0) {
        return {0, glm::vec3(0.0f)};
    }
    // if only one keyframe set. Position equals that keyframe.
    if(mKeyframes.size() == 1) {
        return *mKeyframes.begin();
    }
    // else, check if keyframe is set, return that one.
    Keyframe beforeKeyframe = *mKeyframes.begin();
    Keyframe afterKeyframe = {0, glm::vec3 (0.0f)};
    for(Keyframe keyframe : mKeyframes) {
        if(keyframe.frameIndex == frameIndex) {
            return keyframe;
        }
        if(keyframe.frameIndex > frameIndex) {
            // interpolate
            afterKeyframe = keyframe;
            uint beforeFrameIndex = beforeKeyframe.frameIndex;
            uint afterFrameIndex = afterKeyframe.frameIndex;
            float partition = ((float)(frameIndex-beforeFrameIndex)) / ((float)(afterFrameIndex-beforeFrameIndex));
            glm::vec3 position = beforeKeyframe.pos + partition * (afterKeyframe.pos - beforeKeyframe.pos);
            return {frameIndex, position};
        }
        beforeKeyframe = keyframe;
    }
    // use last value as keyframe
    return mKeyframes.back();
}
