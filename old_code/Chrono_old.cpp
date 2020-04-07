//
// Created by stef on 04.03.20.
//

#include <GLFW/glfw3.h>
#include "Chrono_old.h"

void Chrono_old::reset() {
    mRunning = false;
    mTime = 0;
}


void Chrono_old::start() {
    if(!mRunning) {
        mMomentOfLastUpdate = glfwGetTime();
        mRunning = true;
    }
}


void Chrono_old::pause() {
    if(mRunning) {
        mRunning = false;
        double currTime = glfwGetTime();
        mTime += currTime - mMomentOfLastUpdate;
    }
}


double Chrono_old::getTime() {
    if(mRunning) {
        double currTime = glfwGetTime();
        mTime += currTime - mMomentOfLastUpdate;
        mMomentOfLastUpdate = currTime;
    }
    return mTime;
}
