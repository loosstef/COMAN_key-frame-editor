//
// Created by stef on 15.04.20.
//
#ifndef PROJECT_PICKED_H
#define PROJECT_PICKED_H

//#include "Channel.h"

class StepAheadAnimationChannel;
class CSkeleton;
class FFD;
class CJoint;
class Channel;

class Picked {
public:
//    Picked(Channel *channel = nullptr, FFD *ffd = nullptr, int ctrlPtI = 0) :
//            channel(channel), ffd(ffd), controlPointIndex(ctrlPtI) {}
    Picked() {}
    static Picked nothing();
    static Picked makeStepAheadChannel(StepAheadAnimationChannel *channel, FFD *ffd = nullptr, int ctrlPtI = -1);
    static Picked makeSkeleton(CSkeleton *skl, CJoint *joint = nullptr);
    Channel *channel = nullptr;
    FFD *ffd = nullptr;
    int controlPointIndex = -1;
    CSkeleton *skeleton = nullptr;
    CJoint *joint = nullptr;
};

#endif