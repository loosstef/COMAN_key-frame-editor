//
// Created by stef on 18.02.20.
//

#include <iostream>
#include "Camera.h"
#include "Scene.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


const float MAX_VERTICAL_CAM_ROT = 89.5;
const float MAX_HORIZONTAL_CAM_ROT = 179.5;


/**
 * Constructor
 */
Camera::Camera(int windowWidth, int windowHeight, std::string name) : mModel("base_models/camera.obj") {
    // set standard values
    mName = name;
    mPos = glm::vec3(2.0f, 2.0f, 2.0f);
    mFOV = 45.0f;
    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;
    mNearClipping = 0.01f;
    mfarClipping = 200.0f;
    mTransMat = glm::mat4(1.0f);

    setRotXSafe(-45.0f);
    setRotYSafe(45.0f);
    // set projection matrix
    mProjectionMatrix = genProjectionMatrix(mFOV, windowWidth, windowHeight, mNearClipping, mfarClipping);
}


glm::mat4 Camera::getViewMatrix() {
    glm::mat4 viewMatrix = glm::lookAt(
            calcGlobPos(glm::vec3(0.0f)),
            calcGlobPos(glm::vec3(0.0f, 0.0f, -1.0f)),
            calcGlobPos(glm::vec3(0.0f, 1.0f, 0.0f)) - calcGlobPos(glm::vec3(0.0f))
            );
    return viewMatrix;
}


void Camera::move(glm::vec3 movement) {
    glm::vec3 horizontalViewDir = calcGlobPos(glm::vec3(0.0f, 0.0f, -1.0f));
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


void Camera::relativeMove(glm::vec3 movement) {
//    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(mRotY), glm::vec3(0.0f, 1.0f, 0.0f));
//    rotMat = glm::rotate(rotMat, glm::radians(mRotX), glm::vec3(1.0f, 0.0f, 0.0f));
//    rotMat = glm::rotate(rotMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    glm::vec3 absMoveVec = rotMat * glm::vec4(movement, 1.0f);
    glm::vec3 absNewPos = (glm::vec3)(mTransMat * glm::vec4(movement, 1.0f));
//    mPos += absMoveVec;
    mPos = absNewPos;
    mTransMat = calcTransMat(mPos, mRotX, mRotY);
}


glm::vec3 Camera::calcGlobPos(glm::vec3 pos) {
    glm::vec4 viewDir = mTransMat * glm::vec4(pos, 1.0f);
    return (glm::vec3)viewDir;
//    glm::mat4 rotViewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mRotY), glm::vec3(0.0f, 1.0f, 0.0f));
//    rotViewMatrix = glm::rotate(rotViewMatrix, glm::radians(mRotX), glm::vec3(1.0f, 0.0f, 0.0f));
//    glm::vec4 homogeneViewDir = rotViewMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
//    return glm::vec3(homogeneViewDir.x/homogeneViewDir.w, homogeneViewDir.y/homogeneViewDir.w, homogeneViewDir.z/homogeneViewDir.w);
}


void Camera::rotHor(float angle) {
    setRotYSafe(getRotY() - angle);
}


void Camera::rotVert(float angle) {
    setRotXSafe(getRotX() - angle);
}


void Camera::rot(float horAngle, float verAngle) {
    rotHor(horAngle);
    rotVert(verAngle);
}


void Camera::setRotXSafe(float rotX) {
    if(rotX > MAX_VERTICAL_CAM_ROT ) {
        mRotX = MAX_VERTICAL_CAM_ROT;
    }
    else if(rotX < -MAX_VERTICAL_CAM_ROT) {
        mRotX = -MAX_VERTICAL_CAM_ROT;
    }
    else {
        mRotX = rotX;
    }
    mTransMat = calcTransMat(mPos, mRotX, mRotY);
}

void Camera::setRotYSafe(float rotY) {
    if(rotY > MAX_HORIZONTAL_CAM_ROT) {
        mRotY = -2 * MAX_HORIZONTAL_CAM_ROT + rotY;
    }
    else if(rotY < -MAX_HORIZONTAL_CAM_ROT) {
        mRotY = 2 * MAX_HORIZONTAL_CAM_ROT + rotY;
    }
    else {
        mRotY = rotY;
    }
    mTransMat = calcTransMat(mPos, mRotX, mRotY);
}

glm::mat4 Camera::genProjectionMatrix(float fov, int windowWidth, int windowHeight, float nearClipping, float farClipping) {
    return glm::perspective(
            glm::radians(fov),
            ((float)windowWidth) / ((float)windowHeight),
            nearClipping,
            farClipping
    );
}

void Camera::setWindowSize(int width, int height) {
    mWindowWidth = width;
    mWindowHeight = height;
    mProjectionMatrix = genProjectionMatrix(mFOV, width, height, mNearClipping, mfarClipping);
}

glm::mat4 Camera::calcTransMat(glm::vec3 pos, float rotX, float rotY) {
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), pos);
    transMat = glm::rotate(transMat, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    transMat = glm::rotate(transMat, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    return transMat;
}

void Camera::draw(Scene &scene) {
    Shader *shader = scene.renderEngine().shader();
    // check if render-engine is using correct shader
    if(shader->name().compare("standard") != 0) {
        std::cerr << "[Warning] Camera model not drawn. Using wrong shader." << std::endl;
        return;
    }
    // draw the camera-model
    StandardShader *standardShader = (StandardShader*) shader;
    standardShader->setMatrix(TRANSFORMATION_MATRIX, mTransMat);
//    standardShader->setId(0);
    mModel.draw(0, standardShader->getUniLocTexture());
}

void Camera::setTransformationMatrix(glm::mat4 transMat) {
    mTransMat = transMat;
}

void Camera::update(int frameIndex) {
    if(mPath != nullptr) {
        mTransMat = mPath->orientation(frameIndex);
    }
}

void Camera::setPath(BSplinePath *path) {
    mPath = path;
}
