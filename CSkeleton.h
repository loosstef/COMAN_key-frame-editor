//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CSKELETON_H
#define ANTONGERDELAN_CSKELETON_H


#include <string>
#include "StandardShader.h"
#include "Model.h"

class CJoint;

class CSkeleton {
public:
    CSkeleton(CJoint *joint);
    CSkeleton(std::string filename);
    void render(StandardShader *standardShader);
private:
    void renderJointAndChildren(StandardShader *standardShader, CJoint *joint);
    CJoint *mRootJoint;
    Model mModel;
};


#endif //ANTONGERDELAN_CSKELETON_H
