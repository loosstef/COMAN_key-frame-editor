//
// Created by stef on 15.04.20.
//

#include "FFD.h"
#include <bits/stdc++.h>

const float CONTROL_POINT_SIZE = 0.005;

FFD::FFD(Model &model, int l, int m, int n) : redDot("base_models/red_dot.obj") {
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
                controlPoints[i][j][k] = glm::vec3(i/(float)(l-1), j/(float)(m-1), k/(float)(n-1)); /*P0 + (i/(float)l)*S + (j/(float)m)*T + (k/(float)n)*U;*/
            }
        }
    }
}

void FFD::renderControlPoints(int frameIndex, glm::mat4 transMat, GLint uniLocTransMat, GLint uniLocTexture, Camera &cam) {
    int l = controlPoints.size();
    int m = controlPoints[0].size();
    int n = controlPoints[0][0].size();
    for(int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                glm::vec3 &locPos = controlPoints[i][j][k];
                glm::vec3 globPos = transMat * glm::vec4(P0 + locPos.x * S + locPos.y * T + locPos.z * U, 1.0f);
                float camDist = abs(glm::length(globPos - cam.getPos()));
                glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), globPos);
                transformationMatrix = glm::scale(transformationMatrix, glm::vec3(camDist*CONTROL_POINT_SIZE));
                glUniformMatrix4fv(uniLocTransMat, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
                redDot.Draw(uniLocTexture);
            }
        }
    }
}

glm::vec3 FFD::calcPos(glm::vec3 locPos) {
    float s = locPos.x;
    float t = locPos.y;
    float u = locPos.z;
    int l = (int)controlPoints.size()-1;
    int m = (int)controlPoints[0].size()-1;
    int n = (int)controlPoints[0][0].size()-1;
    glm::vec3 sum(0.0f);
    for(int i = 0; i <= l; ++i) {
        for(int j = 0; j <= m; ++j) {
            for(int k = 0; k <= n; ++k) {
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
    return sum;
}

std::vector<Vertex> FFD::calcPos(std::vector<Vertex> &origGlobPos) {
    std::vector<Vertex> newGlobPositions;
    for(auto &vertex : origGlobPos) {
        newGlobPositions.emplace_back(calcPos(vertex.Position));
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
    return fac(n) / (float)(fac(k)*fac(n-k));
}
