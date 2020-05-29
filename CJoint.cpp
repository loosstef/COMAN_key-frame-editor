//
// Created by stef on 30.03.20.
//

#include "CJoint.h"
#include "CLink.h"
#include "StandardShader.h"
#include <glm/gtc/matrix_transform.hpp>

CJoint::CJoint(float linkOffset, float jointAngle, float minJointAngle, float maxJointAngle, int childrenCount)
  : mModel("base_models/green_cube.obj")
{
    mParentLink = nullptr;
    mLinkOffset = linkOffset;
    mJointAngles.push_back(jointAngle);
    mFrameIndices.push_back(0);
    mCurrJointAngle = jointAngle;
    mMinJointAngle = minJointAngle;
    mMaxJointAngle = maxJointAngle;
    mMaxChildrenCount = childrenCount;
    mGlobalTransMat = glm::mat4(1.0f);
}

CJoint::CJoint(nlohmann::json &j) : mModel("base_models/green_cube.obj") {
    mParentLink = nullptr;
    mId = j["id"];
    mLinkOffset = j["link_offset"];
    mCurrJointAngle = j["joint_angle"];
    mJointAngles = j["joint_angles"].get<std::vector<float>>();
    mFrameIndices = j["frame_indices"].get<std::vector<int>>();
    mMinJointAngle = j["min_joint_angle"];
    mMaxJointAngle = j["max_joint_angle"];
    mMaxChildrenCount = j["max_children_count"];
    mGlobalTransMat = glm::mat4(1.0f);
    for(nlohmann::json &j_child : j["child_links"]) {
        CLink *childLink = new CLink(j_child);
        addChildLink(childLink);
        childLink->setParent(this);
    }
}

void CJoint::setGlobalTransMat(glm::mat4 transMat) {
    mGlobalTransMat = transMat;
    updateLocalTransMat();
    for(int i = 0; i < mMaxChildrenCount; ++i) {
        CJoint *child = mChildLinks[i]->child();
        if(child != nullptr) {
            child->setGlobalTransMat(mGlobalTransMat * mLocalTransMat);
        }
    }
}

/**
 * Update the local transformation matrix, based
 * on the DH-variables locally set.
 */
void CJoint::updateLocalTransMat() {
    // TODO: fix this function
    glm::mat4 rotZArray = {
            glm::cos(mCurrJointAngle), glm::sin(mCurrJointAngle), 0, 0,
            -glm::sin(mCurrJointAngle), glm::cos(mCurrJointAngle), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    glm::mat4 transposeZArray = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, mLinkOffset, 1
    };
    mLocalTransMat = transposeZArray * rotZArray;
    if(mParentLink != nullptr) {
        glm::mat4 rotXArray = {
                1, 0, 0, 0,
                0, glm::cos(mParentLink->linkTwist()), glm::sin(mParentLink->linkTwist()), 0,
                0, -glm::sin(mParentLink->linkTwist()), glm::cos(mParentLink->linkTwist()), 0,
                0, 0, 0, 1
        };
        glm::mat4 translateXArray = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                mParentLink->linkLength(), 0, 0, 1
        };
        mLocalTransMat = translateXArray * rotXArray * mLocalTransMat;
    }
}

void CJoint::setParentLink(CLink *parentLink) {
    mParentLink = parentLink;
}

void CJoint::addChildLink(CLink *childLink) {
    mChildLinks.push_back(childLink);
}

bool CJoint::full() {
    return mChildLinks.size() == mMaxChildrenCount;
}

CLink *CJoint::parent() {
    return mParentLink;
}

void CJoint::renderAll_DEPRECTATED(StandardShader *standardShader) {
    glm::mat4 scaleDown = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));
    glm::mat4 transMat = mGlobalTransMat * mLocalTransMat * scaleDown;
    standardShader->setMatrix(TRANSFORMATION_MATRIX, transMat);
    mModel.draw(0, standardShader->getUniLocTexture());
    for(int i = 0; i < mMaxChildrenCount; ++i) {
        CJoint *child = mChildLinks[i]->child();
        if(child != nullptr) {
            child->renderAll_DEPRECTATED(standardShader);
        }
    }
}

glm::vec3 CJoint::getGlobPos() {
    glm::vec4 globPos = mGlobalTransMat * mLocalTransMat * glm::vec4(glm::vec3(0.0f), 1.0f);
    float w = globPos.w;
    return glm::vec3(globPos.x / w, globPos.y / w, globPos.z / w);
}

glm::mat4 CJoint::transMat() {
    return mGlobalTransMat * mLocalTransMat;
}

glm::vec3 CJoint::getRotAxis() {
    return mGlobalTransMat * mLocalTransMat * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

void CJoint::setJointAngle(float jointAngle, int frameIndex) {
//    mJointAngle_DEPRECATED = jointAngle;
    if(jointAngle < mMinJointAngle)
        jointAngle = mMinJointAngle;
    else if(jointAngle > mMaxJointAngle)
        jointAngle = mMaxJointAngle;

    for(int i = 0; i < mFrameIndices.size(); ++i) {
        if(mFrameIndices[i] == frameIndex) {
            mJointAngles[i] = jointAngle;
            mCurrJointAngle = jointAngle;
            return;
        }
    }
    mJointAngles.push_back(jointAngle);
    mFrameIndices.push_back(frameIndex);
    mCurrJointAngle = jointAngle;
}

float CJoint::calcJointAngle(int frameIndex) {
    if(mFrameIndices.size() == 1) {
        return mJointAngles[0];
    }
    int lowerIndex = -1;
    int lowerFrameIndex = -1;
    int higherIndex = -1;
    int higherFrameIndex = std::numeric_limits<int>::max();
    for(int i = 0; i < mFrameIndices.size(); ++i) {
        if(mFrameIndices[i] == frameIndex) {
            return mJointAngles[i];
        }
        if(mFrameIndices[i] > lowerFrameIndex && mFrameIndices[i] < frameIndex) {
            lowerIndex = i;
            lowerFrameIndex = mFrameIndices[i];
        }
        else if(mFrameIndices[i] < higherFrameIndex && mFrameIndices[i] > frameIndex) {
            higherIndex = i;
            higherFrameIndex = mFrameIndices[i];
        }
    }
    if(lowerIndex == -1) {
        return mJointAngles[higherIndex];
    }
    else if(higherIndex == -1) {
        return mJointAngles[lowerIndex];
    }
    // averaging
    float earlyAngle = mJointAngles[lowerIndex];
    float laterAngle = mJointAngles[higherIndex];
    float factor = (float)(frameIndex-lowerFrameIndex) / (float)(higherFrameIndex-lowerFrameIndex);
    float currAngle = earlyAngle + (factor * (laterAngle-earlyAngle));
    mCurrJointAngle = currAngle;
    return currAngle;
}

void CJoint::setTime(int frameIndex) {
    mCurrJointAngle = calcJointAngle(frameIndex);
    for(int i = 0; i < mMaxChildrenCount; ++i) {
        if(mChildLinks[i] != nullptr) {
            if(mChildLinks[i]->child() != nullptr) {
                mChildLinks[i]->child()->setTime(frameIndex);
            }
        }
    }
}
