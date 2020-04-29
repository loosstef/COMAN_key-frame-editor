//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CLINK_H
#define ANTONGERDELAN_CLINK_H

#include <glm/vec3.hpp>

class CJoint;

class CLink {
public:
    explicit CLink(float linkLength = 0.0f, float linkTwist = 0.0f);
    void setParent(CJoint *joint) { mParentJoint = joint; }
    CJoint *parent() { return mParentJoint; }
    CJoint *child() { return mChildJoint; }
    void setChild(CJoint *childJoint) { mChildJoint = childJoint; }
    float linkLength() { return mLinkLength; }
    float linkTwist() { return mLinkTwist; }
private:
    float mLinkLength;
    float mLinkTwist;
    CJoint *mParentJoint;
    CJoint *mChildJoint;

    glm::vec3 mPoints[2];
    int mIndices[2];

    void setupLink();
};


#endif //ANTONGERDELAN_CLINK_H
