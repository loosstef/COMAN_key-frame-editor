//
// Created by stef on 07.04.20.
//

#include "Clock.h"
#include <GLFW/glfw3.h>
#include <math.h>

int Clock::getFps() {
    return mFps;
}

void Clock::setFps(int fps) {
    mFps = fps;
}

int Clock::getFrameIndex() {
    if(mRunning) {
        // calculate frame-index
        double frameDuration = 1.0 / (double) mFps;
        double currTime = glfwGetTime();
        double deltaTime = currTime - mTimestampLastFrame;
        int diffFrames = floor(deltaTime / frameDuration);
        mFrameIndex += diffFrames;
        mTimestampLastFrame += diffFrames * frameDuration;
    }
    if(mFrameIndex > mLastFrameIndex)
        mFrameIndex = mLastFrameIndex;
    return mFrameIndex;
}

double Clock::getTime() {
    double frameDuration = 1000.0 / (double) mFps;
    return mFrameIndex * mFps;
}

void Clock::setFrameIndex(int frameIndex) {
    if(frameIndex < 0)
        mFrameIndex = 0;
    else if(frameIndex > mLastFrameIndex)
        mFrameIndex = mLastFrameIndex;
    else
        mFrameIndex = frameIndex;
}

void Clock::start() {
    mRunning = true;
    mTimestampLastFrame = glfwGetTime();
}

void Clock::pause() {
    mRunning = false;
}
