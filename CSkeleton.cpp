//
// Created by stef on 30.03.20.
//

#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include "CSkeleton.h"
#include "CLink.h"
#include "CJoint.h"
#include "StandardShader.h"

CSkeleton::CSkeleton(std::string filename)
  : mModelRedDot("base_models/red_dot.obj"),
    mModelOrangeDot("base_models/orange_dot.obj")
  {
    std::ifstream file(filename);
    std::string line;
    mRootJoint = nullptr;
    CJoint *parentJoint = nullptr;
    CLink *parentLink = nullptr;
    while (std::getline(file, line)) {
        // check if line is comment
        if (line[0] == '#') {
            continue;
        }
        else if (line.find("JOINT") != std::string::npos) {
            int posJointAngle = line.find(' ');
            int posLowerBound = line.find(' ', posJointAngle+1);
            int posUpperBound = line.find(' ', posLowerBound+1);
            int posLinkOffset = line.find(' ', posUpperBound+1);
            int posNumberOfChildren = line.find(' ', posLinkOffset+1);
            float jointAngle = std::stof(line.substr(posJointAngle + 1, posLowerBound - posJointAngle));
            float lowerBound = std::stof(line.substr(posLowerBound + 1, posUpperBound - posLowerBound));
            float upperBound = std::stof(line.substr(posUpperBound + 1, posLinkOffset - posUpperBound));
            float linkOffset = std::stof(line.substr(posLinkOffset + 1, posNumberOfChildren - posLinkOffset));
            float numberOfChildren = std::stof(line.substr(posNumberOfChildren + 1));
            CJoint *newJoint = new CJoint(linkOffset, jointAngle, lowerBound, upperBound, numberOfChildren);
            newJoint->setParentLink(parentLink);
            if (mRootJoint == nullptr) {
                mRootJoint = newJoint;
            } else {
                parentLink->setChild(newJoint);
            }
            parentJoint = newJoint;
        } else if (line.find("LINK") != std::string::npos) {
            int posLinkLength = line.find(' ');
            int n = 1;
            while(line[posLinkLength+n] == ' ')
                ++n;
            int posLinkTwist = line.find(' ', posLinkLength+n);
            int posNextJointExist = line.find(' ', posLinkTwist+1);
            float linkLength = std::stof(line.substr(posLinkLength + 1, posLinkTwist - posLinkLength));
            float linkTwist = std::stof(line.substr(posLinkTwist + 1, posNextJointExist - posLinkTwist));
            int nextJointExist = std::stoi(line.substr(posNextJointExist + 1));
            while (parentJoint->full()) {
                parentJoint = parentJoint->parent()->parent();
            }
            CLink *newLink = new CLink(linkLength, linkTwist);
            parentJoint->addChildLink(newLink);
            newLink->setParent(parentJoint);
            if (nextJointExist == 1) {
                parentLink = newLink;
            } else {
                parentJoint = nullptr;
            }
        }
    }
    file.close();
    mRootJoint->setGlobalTransMat(glm::mat4(1.0f));
    initIds(mRootJoint, 0);
}

CSkeleton::CSkeleton(CJoint *joint)
  : mModelRedDot("base_models/red_dot.obj"),
    mModelOrangeDot("base_models/orange_dot.obj")
  {
    mRootJoint = joint;
    joint->setGlobalTransMat(glm::mat4(1.0f));
}

CSkeleton::CSkeleton(nlohmann::json &j)
  : mModelRedDot("base_models/red_dot.obj"),
    mModelOrangeDot("base_models/orange_dot.obj")
{
    mRootJoint = new CJoint(j["root_joint"]);
    mRootJoint->setGlobalTransMat(glm::mat4(1.0f));
}

void CSkeleton::render(StandardShader *standardShader, Picked picked) {
    mRootJoint->setGlobalTransMat(glm::mat4(1.0f));
    int pickedId = -1;
    if(picked.joint !=  nullptr) {
        pickedId = picked.joint->getId();
    }
    renderJointAndChildren(standardShader, mRootJoint, pickedId);
//    mRootJoint->renderAll_DEPRECTATED(standardShader);

}

int CSkeleton::renderForPicking(StandardShader *shader) {
    mRootJoint->setGlobalTransMat(glm::mat4(1.0f));
    renderJoints(shader, mRootJoint);
    shader->setId(0);
}

void CSkeleton::renderJointAndChildren(StandardShader *standardShader, CJoint *joint, int pickedIndex) {
    joint->updateLocalTransMat();
    glm::vec3 pos = joint->getGlobPos();
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), pos);
    transMat = glm::scale(transMat, glm::vec3(0.005f));
    standardShader->setMatrix(TRANSFORMATION_MATRIX, transMat);
    if(joint->getId() != pickedIndex) {
        mModelRedDot.draw(0, standardShader->getUniLocTexture());
    }
    else {
        mModelOrangeDot.draw(0, standardShader->getUniLocTexture());
    }
    for(int i = 0; i < joint->childCount(); ++i) {
        CLink *childLink = joint->childLink(i);
        if(childLink != nullptr) {
            childLink->draw(*standardShader);
            renderJointAndChildren(standardShader, childLink->child(), pickedIndex);
        }
    }
}

void CSkeleton::renderJoints(StandardShader *standardShader, CJoint *joint) {
//    int lastId = jointId;
    joint->updateLocalTransMat();
    glm::vec3 pos = joint->getGlobPos();
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), pos);
    transMat = glm::scale(transMat, glm::vec3(0.005f));
    standardShader->setMatrix(TRANSFORMATION_MATRIX, transMat);
//    standardShader->setId(jointId);
    standardShader->setId(joint->getId()+1);
    mModelRedDot.draw(0, standardShader->getUniLocTexture());
    for(int i = 0; i < joint->childCount(); ++i) {
        CLink *childLink = joint->childLink(i);
        if(childLink != nullptr) {
            renderJoints(standardShader, childLink->child());
//            lastId = renderJoints(standardShader, childLink->child(), lastId+1);
        }
    }
//    return lastId;
}


int CSkeleton::initIds(CJoint *joint, int jointId) {
    joint->setId(jointId);
    int lastId = jointId;
    for(int i = 0; i < joint->childCount(); ++i) {
        CLink *childLink = joint->childLink(i);
        if(childLink != nullptr) {
            lastId = initIds(childLink->child(), lastId+1);
        }
    }
    return lastId;
}

CJoint *CSkeleton::getJoint(int id) {
    return getJoint(id, mRootJoint);
}

CJoint *CSkeleton::getJoint(int id, CJoint *rootJoint) {
    // check if root-joint isn't a nullptr
    if(rootJoint == nullptr) {
        return nullptr;
    }
    // check if root-joint has given id
    if(rootJoint->getId() == id) {
        return rootJoint;
    }
    // search for joint in children
    for(int i = 0; i < rootJoint->childCount(); ++i) {
        CLink *childLink = rootJoint->childLink(i);
        if(childLink != nullptr) {
            CJoint *finding = getJoint(id, childLink->child());
            if(finding != nullptr) {
                // found joint
                return finding;
            }
        }
    }
    // not found beneath given joint
    return nullptr;
}

void CSkeleton::inverseKinematic(CJoint *joint, glm::vec3 newPos) {
    const float CONVERGENCE_THRESHOLD = 0.1f;
    const int MAX_LOOPS = 10;
    const float ROT_FACTOR = 0.1f;
    // check if joint has parents;
    if(joint->parent() == nullptr) {
        return;
    }
    CJoint *rotJoint = joint->parent()->parent();
    int nLoops = 0;
    while((joint->getGlobPos() - newPos).length() > CONVERGENCE_THRESHOLD && nLoops < MAX_LOOPS) {
        if(rotJoint == nullptr) {
            rotJoint = joint->parent()->parent();
            ++nLoops;
        }
        glm::vec3 diffPos = calcDifferential(joint, rotJoint);
        glm::vec3 shouldBeDiff = joint->getGlobPos() - newPos;
        float jointRot = glm::dot(diffPos, shouldBeDiff) * ROT_FACTOR;
        rotJoint->setJointAngle(rotJoint->currJointAngle() - jointRot, mCurrFrame);
        rotJoint->updateLocalTransMat();
        if(rotJoint->parent() != nullptr) {
            rotJoint = rotJoint->parent()->parent();
        }
        else {
            rotJoint = joint->parent()->parent();
            ++nLoops;
        }
    }
}

glm::vec3 CSkeleton::calcDifferential(CJoint *endJoint, CJoint *rotJoint) {
//    const float MINIMAL_ROT = 0.01f;
//    glm::vec3 origPos = endJoint->getGlobPos();
//    rotJoint->setJointAngle(rotJoint->calcJointAngle()+MINIMAL_ROT);
//    rotJoint->updateLocalTransMat();
//    glm::vec3 endPos = endJoint->getGlobPos();
//    rotJoint->setJointAngle(rotJoint->calcJointAngle()-MINIMAL_ROT);
//    rotJoint->updateLocalTransMat();
//    return (endPos-origPos) / MINIMAL_ROT;
    glm::vec3 rotAxis = rotJoint->getRotAxis();
    glm::vec3 arm = endJoint->getGlobPos() - rotJoint->getGlobPos();
    glm::vec3 diff = glm::cross(rotAxis, arm);
    return diff;
}

void CSkeleton::setTime(int frameIndex) {
    if(mCurrFrame != frameIndex) {
        mRootJoint->setTime(frameIndex);
        mCurrFrame = frameIndex;
    }
}
