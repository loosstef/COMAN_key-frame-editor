//
// Created by stef on 18.02.20.
//

#include <iostream>
#include "Navigator.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


const float MAX_VERTICAL_CAM_ROT = 90;
const float MAX_HORIZONTAL_CAM_ROT = 180;


/**
 * Constructor
 */
Navigator::Navigator() {
    mPos = glm::vec3(1.2f, 1.2f, 1.2f);
    setRotXSafe(-45.0f);
    setRotYSafe(45.0f);
}


glm::mat4 Navigator::getViewMatrix() {
    glm::mat4 viewMatrix = glm::lookAt(
            mPos,
            mPos + calcViewDir(),
            glm::vec3(0.0f, 1.0f, 0.0f)
            );
    return viewMatrix;
}


void Navigator::move(glm::vec3 movement) {
    glm::vec3 horizontalViewDir = calcViewDir();
    horizontalViewDir.y = 0;
    horizontalViewDir = glm::normalize(horizontalViewDir);
    // forward or backwards movement
    mPos += horizontalViewDir * movement.z;
    // up or down movement
    mPos += glm::vec3(0.0f, 1.0f, 0.0f) * movement.y;
    // left or right movement
    glm::vec4 sideWaysViewDirHomo = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(horizontalViewDir, 1.0f);
    glm::vec3 sideWaysViewDir = glm::vec3(sideWaysViewDirHomo.x/sideWaysViewDirHomo.w, sideWaysViewDirHomo.y/sideWaysViewDirHomo.w, sideWaysViewDirHomo.z/sideWaysViewDirHomo.w);
    mPos += sideWaysViewDir * movement.x;

}


glm::vec3 Navigator::calcViewDir() {
    glm::mat4 rotViewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mRotY), glm::vec3(0.0f, 1.0f, 0.0f));
    rotViewMatrix = glm::rotate(rotViewMatrix, glm::radians(mRotX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 homogeneViewDir = rotViewMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    return glm::vec3(homogeneViewDir.x/homogeneViewDir.w, homogeneViewDir.y/homogeneViewDir.w, homogeneViewDir.z/homogeneViewDir.w);
}


void Navigator::rotHor(float angle) {
    setRotYSafe(getRotY() - angle);
}


void Navigator::rotVert(float angle) {
    setRotXSafe(getRotX() - angle);
}


void Navigator::rot(float horAngle, float verAngle) {
    rotHor(horAngle);
    rotVert(verAngle);
}


void Navigator::setRotXSafe(float rotX) {
    if(rotX > MAX_VERTICAL_CAM_ROT ) {
        mRotX = MAX_VERTICAL_CAM_ROT;
    }
    else if(rotX < -MAX_VERTICAL_CAM_ROT) {
        mRotX = -MAX_VERTICAL_CAM_ROT;
    }
    else {
        mRotX = rotX;
    }
}

void Navigator::setRotYSafe(float rotY) {
    if(rotY > MAX_HORIZONTAL_CAM_ROT) {
        mRotY = -2 * MAX_HORIZONTAL_CAM_ROT + rotY;
    }
    else if(rotY < -MAX_HORIZONTAL_CAM_ROT) {
        mRotY = 2 * MAX_HORIZONTAL_CAM_ROT + rotY;
    }
    else {
        mRotY = rotY;
    }
}
