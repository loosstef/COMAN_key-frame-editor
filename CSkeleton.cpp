//
// Created by stef on 30.03.20.
//

#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include "CSkeleton.h"
#include "CLink.h"
#include "CJoint.h"
#include "StandardShader.h"

CSkeleton::CSkeleton(std::string filename) : mModel("base_models/red_dot.obj") {
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

CSkeleton::CSkeleton(CJoint *joint) : mModel("base_models/red_dot.obj") {
    mRootJoint = joint;
    joint->setGlobalTransMat(glm::mat4(1.0f));
}

void CSkeleton::render(StandardShader *standardShader) {
    // TODO: add parameter Picked and use it
    mRootJoint->setGlobalTransMat(glm::mat4(1.0f));
    renderJointAndChildren(standardShader, mRootJoint);
//    mRootJoint->renderAll_DEPRECTATED(standardShader);

}

int CSkeleton::renderForPicking(StandardShader *shader) {
    mRootJoint->setGlobalTransMat(glm::mat4(1.0f));
    renderJoints(shader, mRootJoint);
    shader->setId(0);
}

void CSkeleton::renderJointAndChildren(StandardShader *standardShader, CJoint *joint) {
    // TODO: use parameter picked
    joint->updateLocalTransMat();
    glm::vec3 pos = joint->getGlobPos();
    glm::mat4 transMat = glm::translate(glm::mat4(1.0f), pos);
    transMat = glm::scale(transMat, glm::vec3(0.005f));
    standardShader->setMatrix(TRANSFORMATION_MATRIX, transMat);
    mModel.Draw(0, standardShader->getUniLocTexture());
    for(int i = 0; i < joint->childCount(); ++i) {
        CLink *childLink = joint->childLink(i);
        if(childLink != nullptr) {
            childLink->draw(*standardShader);
            renderJointAndChildren(standardShader, childLink->child());
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
    mModel.Draw(0, standardShader->getUniLocTexture());
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
}
