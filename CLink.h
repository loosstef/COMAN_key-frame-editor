//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CLINK_H
#define ANTONGERDELAN_CLINK_H

#include <glm/vec3.hpp>
#include "StandardShader.h"

class CJoint;

class CLink {
public:
    explicit CLink(float linkLength = 0.0f, float linkTwist = 0.0f);
    void setParent(CJoint *joint) { mParentJoint = joint; }
    CJoint *parent() { return mParentJoint; }
    CJoint *child() { return mChildJoint; }
    void setChild(CJoint *childJoint);
    float linkLength() const { return mLinkLength; }
    float linkTwist() { return mLinkTwist; }
    void draw(StandardShader &shader);
private:
    float mLinkLength;
    float mLinkTwist;
    CJoint *mParentJoint;
    CJoint *mChildJoint;

    unsigned int VAO, VBO, EBO;
    glm::vec3 mPoints[2];
    int mIndices[2];

    void setupLink();
};


#endif //ANTONGERDELAN_CLINK_H
