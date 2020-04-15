//
// Created by stef on 15.04.20.
//

#ifndef PROJECT_FFD_H
#define PROJECT_FFD_H


#include <glm/vec3.hpp>
#include <vector>
#include "Model.h"
#include "Camera.h"

class FFD {
public:
    FFD(Model &model, int l, int m, int n);
    void renderControlPoints(int frameIndex, glm::mat4 transMat, GLint uniLocTransMat, GLint uniLocTexture, Camera &cam);
    glm::vec3 calcPos(glm::vec3 locPos);
    std::vector<Vertex> calcPos(std::vector<Vertex> &origGlobPos);
private:
    static int fac(int l);
    static int C(int n, int k);
    glm::vec3 P0 = glm::vec3(0.0f);
    glm::vec3 S = glm::vec3(0.0f);
    glm::vec3 T = glm::vec3(0.0f);
    glm::vec3 U = glm::vec3(0.0f);
    std::vector<std::vector<std::vector<glm::vec3>>> controlPoints;
    Model redDot;
};


#endif //PROJECT_FFD_H
