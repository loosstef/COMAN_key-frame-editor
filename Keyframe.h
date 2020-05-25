//
// Created by stef on 10.04.20.
//

#ifndef PROJECT_KEYFRAME_H
#define PROJECT_KEYFRAME_H


#include <glm/vec3.hpp>

class Keyframe {
public:
    Keyframe(int frameIndex = 0, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
    // getters & setters
    void setFrameIndex(int frameIndex) { mFrameIndex = frameIndex; }
    int& getFrameIndex() { return mFrameIndex; }
    void setPos(glm::vec3 &pos) { mPos = pos; }
    glm::vec3& getPos() { return mPos; }
    void setRot(glm::vec3 &rot) { mRot = rot; }
    glm::vec3& getRot() { return mRot; }
    void setScale(glm::vec3 &scale) { mScale = scale; }
    glm::vec3& getScale() { return mScale; }
private:
    int mFrameIndex;
    glm::vec3 mPos;
    glm::vec3 mRot;
    glm::vec3 mScale;
};


#endif //PROJECT_KEYFRAME_H
