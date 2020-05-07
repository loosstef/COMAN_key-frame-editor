//
// Created by stef on 05.05.20.
//

#ifndef PROJECT_BRANCH_H
#define PROJECT_BRANCH_H

#include <string>
#include <vector>
#include <glm/detail/type_mat4x4.hpp>
#include "StandardShader.h"
#include "Model.h"

class RenderEngine;

class Branch {
public:
    Branch(std::string structure, glm::mat4 transMat, float length = 0.1f);
    void draw(RenderEngine &re, StandardShader &shader);
private:
    void generate(std::string structure, glm::mat4 transMat);
    int findClosingBracket(std::string str, int openBracket);
    void setup();
    unsigned int VAO, VBO, EBO;
    glm::vec3 mPoints[2];
    unsigned int mIndices[2];
    std::vector<Branch> mChildren;
    glm::mat4 mTransMat;
//    glm::mat4 mLocTransMat;
    float mLength;
    float mRotAngle;
    float mChildScale;
    Model redDot;
};


#endif //PROJECT_BRANCH_H
