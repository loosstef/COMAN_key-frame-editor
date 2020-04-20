//
// Created by stef on 15.04.20.
//

//#include <bits/stdc++.h>
#include <string>
#include "FFD.h"
#include "Camera.h"
#include "Keyframe.h"

const float CONTROL_POINT_SIZE = 0.005;
std::string RED_DOT_MODEL_LOCATION("base_models/red_dot.obj");
std::string ORANGE_DOT_MODEL_LOCATION("base_models/orange_dot.obj");

FFD::FFD(Model &model, int l, int m, int n) :
redDot(&RED_DOT_MODEL_LOCATION[0]),
orangeDot(&ORANGE_DOT_MODEL_LOCATION[0])
{
    P0 = glm::vec3(0.0f);
    S = glm::vec3(0.0f);
    T = glm::vec3(0.0f);
    U = glm::vec3(0.0f);
    // get model dimensions
    model.getModelDimensions(P0, S, T, U);
    // place all control-points
    controlPoints.resize(l);
    for(int i = 0; i < l; ++i) {
        controlPoints[i].resize(m);
        for(int j = 0; j < m; ++j) {
            controlPoints[i][j].resize(n);
            for (int k = 0; k < n; ++k) {
                glm::vec3 pos = glm::vec3(i/(float)(l-1), j/(float)(m-1), k/(float)(n-1));
                controlPoints[i][j][k] = pos;
//                controlPoints[i][j][k].addKeyframe(Keyframe(0, pos));
            }
        }
    }
//    allControlPoints.push_back(controlPoints);
//    frameIndices.push_back(0);
}

void FFD::renderControlPoints(glm::mat4 transMat, GLint uniLocTransMat, GLint uniLocTexture, Camera &cam, int pickedDot) {
    int l = controlPoints.size();
    int m = controlPoints[0].size();
    int n = controlPoints[0][0].size();
    int dotID = 1;
    for(int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                glm::vec3 locPos = controlPoints[i][j][k];
                glm::vec3 globPos = transMat * glm::vec4(P0 + locPos.x * S + locPos.y * T + locPos.z * U, 1.0f);
                float camDist = abs(glm::length(globPos - cam.getPos()));
                glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), globPos);
                transformationMatrix = glm::scale(transformationMatrix, glm::vec3(camDist*CONTROL_POINT_SIZE));
                glUniformMatrix4fv(uniLocTransMat, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
                if(dotID == pickedDot) {
                    orangeDot.Draw(0, uniLocTexture);
                } else {
                    redDot.Draw(0, uniLocTexture);
                }
                ++dotID;
            }
        }
    }
}


void FFD::pickControlPoints(glm::mat4 transMat, GLint uniLocTransMat, GLint uniLocTexture, GLint uniLocObjId, Camera &cam) {
    int l = controlPoints.size();
    int m = controlPoints[0].size();
    int n = controlPoints[0][0].size();
    int id = 1;
    for(int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                glm::vec3 locPos = controlPoints[i][j][k];
                glm::vec3 globPos = transMat * glm::vec4(P0 + locPos.x * S + locPos.y * T + locPos.z * U, 1.0f);
                float camDist = abs(glm::length(globPos - cam.getPos()));
                glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), globPos);
                transformationMatrix = glm::scale(transformationMatrix, glm::vec3(camDist*CONTROL_POINT_SIZE));
                glUniformMatrix4fv(uniLocTransMat, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
                glUniform1i(uniLocObjId, id);
                redDot.Draw(0, uniLocTexture);
                ++id;
            }
        }
    }
}

Vertex FFD::calcPos(Vertex locVertex) {
    glm::vec3 &locPos = locVertex.Position;
    float s = (locPos.x-P0.x)/S.x;
    float t = (locPos.y-P0.y)/T.y;
    float u = (locPos.z-P0.z)/U.z;
    int l = (int)controlPoints.size() - 1;
    int m = (int)controlPoints[0].size() - 1;
    int n = (int)controlPoints[0][0].size() - 1;
    glm::vec3 sum(0.0f);
    for(int i = 0; i <= l; ++i) {
        for(int j = 0; j <= m; ++j) {
            for(int k = 0; k <= n; ++k) {
//                glm::vec3 locPijk = controlPoints[i][j][k].orientation(frameIndex).position;
                glm::vec3 locPijk = controlPoints[i][j][k];
                glm::vec3 Pijk = P0 + locPijk[0] * S + locPijk[1] * T + locPijk[2] * U;
                float factor = (float)(FFD::C(l, i) * FFD::C(m, j) * FFD::C(n, k));
                factor *= (float)(std::pow(1-s, l-i) * std::pow(s, i));
                factor *= (float)(std::pow(1-t, m-j) * std::pow(t, j));
                factor *= (float)(std::pow(1-u, n-k) * std::pow(u, k));
                sum += factor * Pijk;
            }
        }
    }
    return {sum, locVertex.Normal, locVertex.TexCoords};
}

std::vector<Vertex> FFD::calcPos_debug(std::vector<Vertex> &origGlobPos) {
    std::vector<Vertex> newGlobPositions;
    for(auto &vertex : origGlobPos) {
        newGlobPositions.emplace_back(calcPos(vertex));
    }
    return newGlobPositions;
}

int FFD::fac(int l) {
    int factorial = 1;
    for(int i = 2; i <= l; ++i) {
        factorial *= i;
    }
    return factorial;
}

int FFD::C(int n, int k) {
//    return fac(n) / (float)(fac(k)*fac(n-k));
    if (k == 0 || k == n)
        return 1;
    return C(n - 1, k - 1) + C(n - 1, k);
}

void FFD::setControlPoint(glm::tvec3<int> index, glm::vec3 pos) {
    controlPoints[index.x][index.y][index.z] = pos;
//    controlPoints[index.x][index.y][index.z].addKeyframe(Keyframe(frameIndex, pos));
}

//void FFD::setFrameIndex(int frameIndex) {
//    if(currFrameIndex == frameIndex) {
//        return;
//    }
//}
