//
// Created by stef on 18.02.20.
//

#ifndef ANTONGERDELAN_NAVIGATOR_H
#define ANTONGERDELAN_NAVIGATOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"

class Scene;

class Camera {
public:
    Camera(int windowWidth, int windowHeight);
    glm::mat4 getViewMatrix();
    void rot(float horAngle, float verAngle);
    void move(glm::vec3 movement);
    void relativeMove(glm::vec3 movement);
    void setWindowSize(int width, int height);
    // drawing camera
    void draw(Scene &scene);
    // getters
    glm::vec3 getPos() { return mPos; }
    glm::mat4 getProjectionMatrix() { return mProjectionMatrix; }
private:
    glm::vec3 calcViewDir();
    void rotHor(float angle);
    void rotVert(float angle);
    float getRotX() { return mRotX; }
    float getRotY() { return mRotY; }
    void setRotXSafe(float rotX);
    void setRotYSafe(float rotY);
    glm::mat4 genProjectionMatrix(float fov, int windowWidth, int windowHeight, float nearClipping, float farClipping);
    static glm::mat4 calcTransMat(glm::vec3 pos, float rotX, float rotY);
    // camera settings
    float mFOV;
    int mWindowWidth;
    int mWindowHeight;
    float mNearClipping;
    float mfarClipping;
    // drawing
    Model mModel;
    glm::mat4 mTransMat;

    glm::vec3 mPos;
    float mRotX, mRotY;
    glm::mat4 mProjectionMatrix;
};


#endif //ANTONGERDELAN_NAVIGATOR_H
