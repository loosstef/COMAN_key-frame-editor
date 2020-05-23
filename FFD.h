//
// Created by stef on 15.04.20.
//

#ifndef PROJECT_FFD_H
#define PROJECT_FFD_H


#include <glm/vec3.hpp>
#include <vector>
#include "Model.h"
#include "LinearPath.h"

class Camera;

class FFD {
public:
    FFD(Model &model, int l, int m, int n);
    void renderControlPoints(glm::mat4 transMat, GLint uniLocTransMat, GLint uniLocTexture, Camera &cam, int pickedDot = -1);
    void pickControlPoints(glm::mat4 transMat, GLint uniLocTransMat, GLint uniLocTexture, GLint uniLocObjId, Camera &cam);
    Vertex calcPos(Vertex locPos);
    std::vector<Vertex> calcPos_debug(std::vector<Vertex> &origGlobPos);
    void setControlPoint(glm::tvec3<int> index, glm::vec3 pos);
    void setControlPoint(int index, glm::vec3 pos);
    void setControlPointAbsCoord(glm::tvec3<int> index, glm::vec3 pos);
    void setControlPointAbsCoord(int index, glm::vec3 pos);
    glm::vec3 getLocalAbsoluteLoc(glm::tvec3<int> index);
    glm::vec3 getLocalAbsoluteLoc(int index);
//    void setFrameIndex(int frameIndex);
    nlohmann::json to_json();
private:
    glm::tvec3<int> flatIndexToFullIndex(int index);
    glm::vec3 absToRelCoords(glm::vec3 coords);
    static int fac(int l);
    static int C(int n, int k);
    glm::vec3 P0 = glm::vec3(0.0f);
    glm::vec3 S = glm::vec3(0.0f);
    glm::vec3 T = glm::vec3(0.0f);
    glm::vec3 U = glm::vec3(0.0f);
    std::vector<std::vector<std::vector<glm::vec3>>> controlPoints;
    Model redDot;
    Model orangeDot;
};


#endif //PROJECT_FFD_H
