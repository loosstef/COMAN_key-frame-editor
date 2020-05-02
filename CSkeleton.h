//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CSKELETON_H
#define ANTONGERDELAN_CSKELETON_H


#include <string>
#include "Model.h"
#include "Picked.h"

class CJoint;
class StandardShader;

class CSkeleton {
public:
    CSkeleton(CJoint *joint);
    CSkeleton(std::string filename);
    void render(StandardShader *standardShader);
    int renderForPicking(StandardShader *shader);
private:
    void renderJointAndChildren(StandardShader *standardShader, CJoint *joint);
    void renderJoints(StandardShader *standardShader, CJoint *joint);
    int initIds(CJoint *joint, int jointId);
    CJoint *mRootJoint;
    Model mModel;
};


#endif //ANTONGERDELAN_CSKELETON_H
