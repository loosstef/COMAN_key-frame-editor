//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CSKELETON_H
#define ANTONGERDELAN_CSKELETON_H


#include "CJoint.h"

class CSkeleton {
public:
    CSkeleton(CJoint *rootJoint) { mRootJoint = rootJoint; }
private:
    CJoint *mRootJoint;
};


#endif //ANTONGERDELAN_CSKELETON_H
