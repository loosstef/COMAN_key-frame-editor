//
// Created by stef on 04.03.20.
//

#include <GLFW/glfw3.h>
#include "Chrono.h"

void Chrono::reset() {
    mRunning = false;
    mTime = 0;
}


void Chrono::start() {
    if(!mRunning) {
        mMomentOfLastUpdate = glfwGetTime();
        mRunning = true;
    }
}


void Chrono::pause() {
    if(mRunning) {
        mRunning = false;
        double currTime = glfwGetTime();
        mTime += currTime - mMomentOfLastUpdate;
    }
}


double Chrono::getTime() {
    if(mRunning) {
        double currTime = glfwGetTime();
        mTime += currTime - mMomentOfLastUpdate;
        mMomentOfLastUpdate = currTime;
    }
    return mTime;
}
