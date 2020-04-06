//
// Created by stef on 03.03.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Mover.h"

const float DURATION = 5.0f;

Mover::Mover(Object &obj, Path &path) : mObject(obj), mPath(path) {
}

glm::mat4 Mover::translation(float time) {
    glm::mat4 modelMatrix(1.0f);
    float arcLength = time / DURATION;
    while(arcLength > 1.0f) {
        arcLength -= 1.0f;
    }
    glm::vec3 newPos = mPath.valueArcLength(arcLength);
    modelMatrix = glm::translate(modelMatrix, newPos);
    return modelMatrix;
}

void Mover::draw(GLint uniTrans) {
    double moveTime = mChrono.getTime();
    glm::mat4 modelMatrix = translation(moveTime);
    mObject.draw(uniTrans, modelMatrix);
}

void Mover::start() {
    mChrono.start();
}

void Mover::pause() {
    mChrono.pause();
}
