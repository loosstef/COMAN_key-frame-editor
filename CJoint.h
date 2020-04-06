//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CJOINT_H
#define ANTONGERDELAN_CJOINT_H


#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <forward_list>
#include "CLink.h"

class CJoint {
public:
    CJoint(float linkOffset=0.0f, float jointAngle=0.0f, float minJointAngle=0.0f, float maxJointAngle=360.0f);
private:
    void updateLocalTransMat();
    float mLinkOffset;
    float mJointAngle;
    float mMinJointAngle;
    float mMaxJointAngle;
    glm::mat4 mLocalTransMat;
    glm::mat4 mGlobalTransMat;
//    CLink *mParentLink;
//    std::forward_list<CLink*> mChildLinks;
};


#endif //ANTONGERDELAN_CJOINT_H
