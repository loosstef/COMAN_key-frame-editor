//
// Created by stef on 30.03.20.
//

#ifndef ANTONGERDELAN_CJOINT_H
#define ANTONGERDELAN_CJOINT_H


#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <vector>
#include <vector>
#include "Model.h"

class CLink;
class StandardShader;

class CJoint {
public:
    CJoint(float linkOffset=0.0f, float jointAngle=0.0f, float minJointAngle=0.0f, float maxJointAngle=360.0f, int mChildrenCount = 0);
    void setParentLink(CLink *parentLink);
    void addChildLink(CLink *childLink);
    bool full();
    CLink *parent();
    void setGlobalTransMat(glm::mat4 transMat);
    glm::vec3 getGlobPos();
    int childCount() { return mMaxChildrenCount; }
    CLink *childLink(int index) { return mChildLinks[index]; }
    void updateLocalTransMat();
    glm::mat4 transMat();
    float offset() { return mLinkOffset; }
    void setId(int id) { mId = id; }
    int getId() { return mId; }
    float getJointAngle() { return mJointAngle_DEPRECATED; }
    void setJointAngle(float jointAngle);
    glm::vec3 getRotAxis();
    // DEPRECATED FUNCTIONS
    void renderAll_DEPRECTATED(StandardShader *standardShader);
    // IMGUI FUNCTIONS
//    float* ImGui_linkOffset() { return &mLinkOffset; }
    float* ImGui_jointAngle() { return &mJointAngle_DEPRECATED; }
    float* ImGui_minJointAngle() { return &mMinJointAngle; }
    float* ImGui_maxJointAngle() { return &mMaxJointAngle; }
private:
    int mId = -1;
    float mLinkOffset;
    float mJointAngle_DEPRECATED;
    std::vector<float> mJointAngles;
    std::vector<int> mFrameIndices;
    float mMinJointAngle;
    float mMaxJointAngle;
    int mMaxChildrenCount;
    glm::mat4 mLocalTransMat;
    glm::mat4 mGlobalTransMat;
    CLink *mParentLink;
    std::vector<CLink*> mChildLinks;
    Model mModel;
};


#endif //ANTONGERDELAN_CJOINT_H
