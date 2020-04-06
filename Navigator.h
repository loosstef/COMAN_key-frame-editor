//
// Created by stef on 18.02.20.
//

#ifndef ANTONGERDELAN_NAVIGATOR_H
#define ANTONGERDELAN_NAVIGATOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Navigator {
public:
    Navigator();
    glm::mat4 getViewMatrix();
    void rot(float horAngle, float verAngle);
    void move(glm::vec3 movement);
private:
    glm::vec3 calcViewDir();
    void rotHor(float angle);
    void rotVert(float angle);
    float getRotX() { return mRotX; }
    float getRotY() { return mRotY; }
    void setRotXSafe(float rotX);
    void setRotYSafe(float rotY);

    glm::vec3 mPos;
    float mRotX, mRotY;
};


#endif //ANTONGERDELAN_NAVIGATOR_H
