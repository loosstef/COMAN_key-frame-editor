//
// Created by stef on 06.04.20.
//

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include "StepAheadAnimationChannel.h"
#include "Path.h"
#include "Keyframe.h"
#include "Model.h"
#include "FFD.h"


void StepAheadAnimationChannel::setPath(Path *path) {
    mPath = path;
}


void StepAheadAnimationChannel::setObject(Model *model) {
    mModel = model;
}

void StepAheadAnimationChannel::addFFD(int frameIndex, FFD *ffd) {
    mFFDs.push_back(ffd);
    mFFFDFrameIndices.push_back(frameIndex);
    mModel->applyFFD(frameIndex, ffd);
}

FFD *StepAheadAnimationChannel::getFFD(int frameIndex) {
    for(int i = 0; i < mFFFDFrameIndices.size(); ++i) {
        if(mFFFDFrameIndices[i] == frameIndex)
            return mFFDs[i];
    }
    return nullptr;
}
