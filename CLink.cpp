//
// Created by stef on 30.03.20.
//

#include "CLink.h"
#include "CJoint.h"

CLink::CLink(float linkLength, float linkTwist) {
    mLinkLength = linkLength;
    mLinkTwist = linkTwist;

    mPoints[0] = glm::vec3(0.0f);
    mPoints[1] = glm::vec3(linkLength, 0.0f, 0.0f);
    mIndices[0] = 0;
    mIndices[1] = 1;
}

void CLink::setupLink() {

}
