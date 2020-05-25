//
// Created by stef on 06.04.20.
//

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "StepAheadAnimationChannel.h"
#include "Path.h"
#include "Keyframe.h"
#include "Model.h"
#include "FFD.h"
#include "jsonCast.h"

StepAheadAnimationChannel::StepAheadAnimationChannel(nlohmann::json j) {
    mModel = new Model(j["model_filename"].get<std::string>().data());
    for(nlohmann::json j_ffd : j["FFDs"]) {
        mFFDs.push_back(new FFD(j_ffd));
    }
}

void StepAheadAnimationChannel::setPath(LinearPath *path) {
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

void StepAheadAnimationChannel::setTransMat(glm::mat4 &mat) {
    mTransMat = mat;
}

glm::mat4 StepAheadAnimationChannel::getTransMat() {
    return mTransMat;
}

void StepAheadAnimationChannel::prepare(int frameIndex) {
    if(mPath == nullptr) {
        mTransMat = glm::mat4(1.0f);
        return;
    }
    Orientation orientation = mPath->orientation(frameIndex);
    glm::mat4 rotMat = glm::toMat4(orientation.rotation);
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), orientation.position);
    glm::mat4 transformationMatrix = glm::scale(transMat*rotMat, orientation.scale);
    mTransMat = transformationMatrix;
    return;
}

void StepAheadAnimationChannel::tellModelFFDChanged(FFD *ffd, int frameIndex) {
    mModel->applyFFD(frameIndex, ffd);
//    mModel->onFFDChange();
}

void StepAheadAnimationChannel::removeFFD(int frameIndex) {
    for(int i = 0; i < mFFFDFrameIndices.size(); ++i) {
        if(mFFFDFrameIndices[i] == frameIndex) {
            mFFFDFrameIndices.erase(mFFFDFrameIndices.begin()+i);
            mFFDs.erase(mFFDs.begin()+i);
            mModel->removeFFD(frameIndex);
        }
    }
}

nlohmann::json StepAheadAnimationChannel::to_json() {
    nlohmann::json j;
    j["model_filename"] = mModel->getPath();
    j["keyframes"] = mPath->to_json();
    nlohmann::json j_FFDs = nlohmann::json::array();
    for(auto &FFD : mFFDs) {
        j_FFDs.push_back(*FFD);
    }
    j["FFDs"] = j_FFDs;
    return j;
}
