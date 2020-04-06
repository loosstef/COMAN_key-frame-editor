//
// Created by stef on 30.03.20.
//

#include "CJoint.h"

CJoint::CJoint(float linkOffset, float jointAngle, float minJointAngle, float maxJointAngle) {
    mLinkOffset = linkOffset;
    mJointAngle = jointAngle;
    mMinJointAngle = minJointAngle;
    mMaxJointAngle = maxJointAngle;
}

/**
 * Update the local transformation matrix, based
 * on the DH-variables locally set.
 */
void CJoint::updateLocalTransMat() {
    float rotZArray[16] = {
            glm::cos(mJointAngle), glm::sin(mJointAngle), 0, 0,
            -glm::sin(mJointAngle), glm::cos(mJointAngle), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    float transposeZArray[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, mLinkOffset, 1
    };
}
