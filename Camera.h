//
// Created by stef on 18.02.20.
//

#ifndef ANTONGERDELAN_NAVIGATOR_H
#define ANTONGERDELAN_NAVIGATOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera(int windowWidth, int windowHeight);
    glm::mat4 getViewMatrix();
    void rot(float horAngle, float verAngle);
    void move(glm::vec3 movement);
    void relativeMove(glm::vec3 movement);
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

    glm::vec3 mPos;
    float mRotX, mRotY;
    glm::mat4 mProjectionMatrix;
};


#endif //ANTONGERDELAN_NAVIGATOR_H
