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
    void render(StandardShader *standardShader, Picked picked);
    int renderForPicking(StandardShader *shader);
    CJoint *getJoint(int id);
    void inverseKinematic(CJoint *joint, glm::vec3 newPos);
    void setTime(int frameIndex);
private:
    void renderJointAndChildren(StandardShader *standardShader, CJoint *joint, int pickedIndex);
    void renderJoints(StandardShader *standardShader, CJoint *joint);
    int initIds(CJoint *joint, int jointId);
    CJoint *getJoint(int id, CJoint *rootJoint);
    glm::vec3 calcDifferential(CJoint *endJoint, CJoint *rotJoint);
    CJoint *mRootJoint;
    Model mModelRedDot;
    Model mModelOrangeDot;
    int mCurrFrame = 0;
};


#endif //ANTONGERDELAN_CSKELETON_H
