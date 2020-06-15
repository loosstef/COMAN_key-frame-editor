//
// Created by stef on 06.04.20.
//

#include "LinearPath.h"
#include "Keyframe.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include "jsonCast.h"

LinearPath::LinearPath(nlohmann::json j) {
    for(nlohmann::json j_keyframe : j) {
        Keyframe keyframe = j_keyframe;
        addKeyframe(keyframe);
    }
}

void LinearPath::addKeyframe(Keyframe newKeyframe) {
    for(auto it = mKeyframes.begin(); it != mKeyframes.end(); it++) {
        if(it->getFrameIndex() == newKeyframe.getFrameIndex()) {
            it->getPos() = newKeyframe.getPos();
            return;
        }
        else if(it->getFrameIndex() > newKeyframe.getFrameIndex()) {
            mKeyframes.insert(it, newKeyframe);
            return;
        }
    }
    mKeyframes.push_back(newKeyframe);
}


bool LinearPath::hasKeyframe(uint frameIndex) {
    for(Keyframe keyframe : mKeyframes) {
        if(keyframe.getFrameIndex() == frameIndex)
            return true;
        else if(keyframe.getFrameIndex() > frameIndex)
            return false;
    }
    return false;
}


 /**
  * Calculate the position and rotation of an object following this path at a given frame-index.
  * @param frameIndex
  * @return
  */
Orientation LinearPath::orientation(int frameIndex) {
    // if no keyframes set yet. Orientation should be the standard one.
    if(mKeyframes.empty()) {
        return {};
    }
    // if only one keyframe set. Position equals that keyframe.
    if (mKeyframes.size() == 1) {
        Keyframe &keyframe = *mKeyframes.begin();
        return {keyframe.getPos(), keyframe.getRot(), keyframe.getScale()};
    }
    // if first keyframe is later than querried one --> use that one
    if(mKeyframes.begin()->getFrameIndex() > frameIndex) {
        return Orientation(*mKeyframes.begin());
    }
    // If frame contains a keyframe, return that keyframe his orientation
    Keyframe beforeKeyframe = *mKeyframes.begin();
    Keyframe afterKeyframe = Keyframe(0);
    for (Keyframe &keyframe : mKeyframes) {
         // return orientation if frame-index contains a keyframe
         if (keyframe.getFrameIndex() == frameIndex) {
            glm::mat4x4 euler = glm::eulerAngleYXZ(keyframe.getRot().y, keyframe.getRot().x, keyframe.getRot().z);
            glm::quat quat = glm::toQuat(euler);
            glm::vec3 interpEuler = glm::eulerAngles(quat);
            return Orientation(keyframe.getPos(), interpEuler, keyframe.getScale());
         }
         if (keyframe.getFrameIndex() > frameIndex) {
             // interpolate
             afterKeyframe = keyframe;
             break;
         }
         beforeKeyframe = keyframe;
    }
    // if no keyframe was found that has higher or matching keyframe than the searched one: return last keyframe
    if(afterKeyframe.getFrameIndex() <= frameIndex) {
        return {mKeyframes.back().getPos(), mKeyframes.back().getRot(), mKeyframes.back().getScale()};
    }
    // interpolate and generate keyframe
    int beforeFrameIndex = beforeKeyframe.getFrameIndex();
    int afterFrameIndex = afterKeyframe.getFrameIndex();
    float partition =
             ((float) (frameIndex - beforeFrameIndex)) / ((float) (afterFrameIndex - beforeFrameIndex));
    glm::vec3 position = linearInterpolate(beforeKeyframe.getPos(), afterKeyframe.getPos(), partition);
    glm::quat rotation = linearInterpolateRotation(beforeKeyframe.getRot(), afterKeyframe.getRot(), partition);
    glm::vec3 scale = linearInterpolate(beforeKeyframe.getScale(), afterKeyframe.getScale(), partition);
    return Orientation(position, rotation, scale);
}


glm::vec3 LinearPath::linearInterpolate(glm::vec3 &vec1, glm::vec3 &vec2, float factor) {
    return vec1 + (factor * (vec2 - vec1));
    return glm::vec3();
}


glm::quat LinearPath::linearInterpolateRotation(glm::vec3 &rot1, glm::vec3 &rot2, float factor) {
    if(factor < 0)
        factor = 0.0f;
    else if(factor > 1)
        factor = 1.0f;

    glm::mat4x4 euler1 = glm::eulerAngleYXZ(rot1.y, rot1.x, rot1.z);
    glm::mat4x4 euler2 = glm::eulerAngleYXZ(rot2.y, rot2.x, rot2.z);

    glm::quat quat1 = glm::toQuat(euler1);
    glm::quat quat2 = glm::toQuat(euler2);

    glm::quat interpQuat = glm::mix(quat1, quat2, factor);
    return interpQuat;
}


nlohmann::json LinearPath::to_json() {
    nlohmann::json j_keyframes = nlohmann::json::array();
    for(auto keyframe : mKeyframes) {
        nlohmann::json j_keyframe = {
                {"frame_index", keyframe.getFrameIndex()},
                {"position", {keyframe.getPos().x, keyframe.getPos().y, keyframe.getPos().z}},
                {"rotation", {keyframe.getRot().x, keyframe.getRot().y, keyframe.getRot().z}},
                {"scale", {keyframe.getScale().x, keyframe.getScale().y, keyframe.getScale().z}}
        };
        j_keyframes.push_back(j_keyframe);
    }
    return j_keyframes;
}
