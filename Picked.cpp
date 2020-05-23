//
// Created by stef on 01.05.20.
//

#include "Picked.h"
#include "StepAheadAnimationChannel.h"
#include "CSkeleton.h"
#include "FFD.h"
#include "CJoint.h"

Picked Picked::nothing() {
    return {};
}

Picked Picked::makeStepAheadChannel(StepAheadAnimationChannel *channel, FFD *ffd, int ctrlPtI) {
    Picked val;
    val.channel = channel;
    val.ffd = ffd;
    val.controlPointIndex = ctrlPtI;
    return val;
}

Picked Picked::makeSkeleton(CSkeleton *skl, CJoint *joint) {
    Picked val;
    val.skeleton = skl;
    val.joint = joint;
    return val;
}
