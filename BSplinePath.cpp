//
// Created by stef on 16.05.20.
//

#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include "BSplinePath.h"
#include "BSpline.h"

void BSplinePath::add(BSpline *bSpline, std::pair<int, int> range) {
    mBSplines.push_back(bSpline);
    mIndexRanges.push_back(range);
}

glm::mat4 BSplinePath::orientation(int frameIndex) {
    glm::mat4 rotMat = glm::toMat4(calcRot(frameIndex));
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), calcPos(frameIndex));
    transMat = transMat * rotMat;
    return transMat;
}

glm::vec3 BSplinePath::calcPos(int frameIndex) {
    int lowerFrameDist = std::numeric_limits<int>::max();
    glm::vec3 interpPos = glm::vec3(0.0f);
    for(int i = 0; i < mIndexRanges.size(); ++i) {
        auto &range = mIndexRanges[i];
        auto &bSpline = mBSplines[i];
        if(range.first <= frameIndex && frameIndex < range.second) {
            float p = (frameIndex-range.first) / (float)(range.second-range.first);
            glm::vec3 pos = bSpline->valueArcLength(p);
            return pos;
        }
        if(std::abs(range.first-frameIndex) < lowerFrameDist) {
            lowerFrameDist = std::abs(range.first-frameIndex);
            interpPos = bSpline->valueParametric(0);
        }
        if(std::abs(range.second-frameIndex) < lowerFrameDist) {
            lowerFrameDist = std::abs(range.second-frameIndex);
            interpPos = bSpline->valueParametric(1);
        }
    }
    return interpPos;
}

glm::quat BSplinePath::calcRot(int frameIndex) {
    // check if rotation exists
    if(mRotations.empty()) {
        glm::vec3 rot(0.0f);
        glm::mat4x4 euler = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);
        glm::quat quat = glm::toQuat(euler);
        return quat;
    }
    // return rotation if only one present
    if(mRotations.size() == 1) {
        glm::vec3 rot = mRotations.begin()->second;
        glm::mat4x4 euler = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);
        glm::quat quat = glm::toQuat(euler);
        return quat;
    }
    // check if contains key
    auto it = mRotations.find(frameIndex);
    if(it != mRotations.end()) {
        glm::vec3 rot = it->second;
        glm::mat4x4 euler = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);
        glm::quat quat = glm::toQuat(euler);
//        glm::vec3 interpEuler = glm::eulerAngles(quat);
//        return Orientation(keyframe.getPos(), interpEuler, keyframe.getScale());
        return quat;
    }

    auto afterIt = mRotations.upper_bound(frameIndex);
    if(afterIt == mRotations.end()) {
        glm::vec3 rot = (--mRotations.end())->second;
        glm::mat4x4 euler = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);
        glm::quat quat = glm::toQuat(euler);
        return quat;
    }
    if(afterIt == mRotations.begin()) {
        glm::vec3 rot = afterIt->second;
        glm::mat4x4 euler = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);
        glm::quat quat = glm::toQuat(euler);
        return quat;
    }
    auto beforeIt = afterIt;
    --beforeIt;
    // interpolate
    float partition = ((float) (frameIndex - beforeIt->first)) / ((float) (afterIt->first - beforeIt->first));
    glm::quat rotation = linearInterpolateRotation(beforeIt->second, afterIt->second, partition);
    return rotation;
}

glm::quat BSplinePath::linearInterpolateRotation(glm::vec3 &rot1, glm::vec3 &rot2, float factor) {
    // check if factor is in bounds [0,1]
    if(factor < 0)
        factor = 0.0f;
    else if(factor > 1)
        factor = 1.0f;
    // euler matrices
    glm::mat4x4 euler1 = glm::eulerAngleYXZ(rot1.y, rot1.x, rot1.z);
    glm::mat4x4 euler2 = glm::eulerAngleYXZ(rot2.y, rot2.x, rot2.z);
    // quaternions
    glm::quat quat1 = glm::toQuat(euler1);
    glm::quat quat2 = glm::toQuat(euler2);
    // interpolate and return
    glm::quat interpQuat = glm::mix(quat1, quat2, factor);
    return interpQuat;
}

void BSplinePath::add(glm::vec3 rotation, int frameIndex) {
    rotation = glm::radians(rotation);
    mRotations.erase(frameIndex);
    mRotations.insert(std::pair<int, glm::vec3>(frameIndex, rotation));
}
