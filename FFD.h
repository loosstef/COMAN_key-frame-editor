//
// Created by stef on 15.04.20.
//

#ifndef PROJECT_FFD_H
#define PROJECT_FFD_H


#include "jsonCast.h"
#include <glm/vec3.hpp>
#include <vector>
#include "Model.h"
#include "LinearPath.h"

class Camera;

class FFD {
public:
    // constructor
    FFD(Model &model, int l, int m, int n);
    FFD(nlohmann::json j);
    void init(const nlohmann::json &j);
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
    // getters
    [[nodiscard]] glm::vec3 getP0() const { return P0; }
    [[nodiscard]] glm::vec3 getS() const { return S; }
    [[nodiscard]] glm::vec3 getT() const { return T; }
    [[nodiscard]] glm::vec3 getU() const { return U; }
    [[nodiscard]] nlohmann::json getControlPointsJson() const { return controlPoints; }

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
