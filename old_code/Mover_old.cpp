//
// Created by stef on 03.03.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Mover_old.h"

const float DURATION = 5.0f;

Mover_old::Mover_old(Object &obj, Path_old &path) : mObject(obj), mPath(path) {
}

glm::mat4 Mover_old::translation(float time) {
    glm::mat4 modelMatrix(1.0f);
    float arcLength = time / DURATION;
    while(arcLength > 1.0f) {
        arcLength -= 1.0f;
    }
    glm::vec3 newPos = mPath.valueArcLength(arcLength);
    modelMatrix = glm::translate(modelMatrix, newPos);
    return modelMatrix;
}

void Mover_old::draw(GLint uniTrans) {
    double moveTime = mChrono.getTime();
    glm::mat4 modelMatrix = translation(moveTime);
    mObject.draw(uniTrans, modelMatrix);
}

void Mover_old::start() {
    mChrono.start();
}

void Mover_old::pause() {
    mChrono.pause();
}
