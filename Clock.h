//
// Created by stef on 07.04.20.
//

#ifndef PROJECT_CLOCK_H
#define PROJECT_CLOCK_H


class Clock {
public:
    int getFps();
    void setFps(int fps);
    int getFrameIndex();
    double getTime();
    void setFrameIndex(int frameIndex);
    void start();
    void pause();
    bool isRunning() { return mRunning; }

    // functions that may only be called by windowing code
    int* imGui_frameIndex() { return &mFrameIndex; }
    int* imGui_fps() { return &mFps; }
    int* imGui_lastFrameIndex() { return &mLastFrameIndex; }
private:
    int mFrameIndex = 0;
    int mFps = 60;
    double mTimestampLastFrame = 0;
    bool mRunning = false;
    int mLastFrameIndex = 600;
};


#endif //PROJECT_CLOCK_H
