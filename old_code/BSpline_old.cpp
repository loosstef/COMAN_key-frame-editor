//
// Created by stef on 26.02.20.
//

#include <glm/gtc/type_ptr.hpp>
#include "BSpline_old.h"

float MATRIX_ARRAY[16] = {-1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0};
glm::mat4 MATRIX(-1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0);


BSpline_old::BSpline_old(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) : Path_old(nullptr, 0, GL_LINE_STRIP) {
    mKnotVector.push_back(p1);
    mKnotVector.push_back(p2);
    mKnotVector.push_back(p3);
    mKnotVector.push_back(p4);
}

BSpline_old::BSpline_old(glm::vec3 pBegin, std::vector<glm::vec3> otherKnots, glm::vec3 pEnd) {
    mKnotVector.push_back(pBegin);
    mKnotVector.push_back(pBegin);
    mKnotVector.push_back(pBegin);
    for(auto &knot : otherKnots) {
        mKnotVector.push_back(knot);
    }
    mKnotVector.push_back(pEnd);
    mKnotVector.push_back(pEnd);
    mKnotVector.push_back(pEnd);
}

void BSpline_old::add(glm::vec3 knot) {
    mKnotVector.push_back(knot);
}


void BSpline_old::add(int index, glm::vec3 knot) {
    auto it = mKnotVector.begin()+index;
    mKnotVector.insert(it, knot);
}


glm::vec3 BSpline_old::valueParametric(int i, float u) {
    if(i > mKnotVector.size()-3 || i < 0) {
        throw "ERROR. Can't get valueParametric of B-Spline. Value i is too big";
    }

    glm::vec4 weights = 1.0f / 6.0f * glm::vec4(u*u*u, u*u, u, 1.0f) * MATRIX;
    glm::mat4x3 pointMat(mKnotVector[i], mKnotVector[i+1], mKnotVector[i+2], mKnotVector[i+3]);
    return pointMat * weights;
}


glm::vec3 BSpline_old::valueParametric(float u) {
    int n = mKnotVector.size();
    if(u == 1) {
        return valueParametric(n - 4, 1);
    }
    float number = (u * (n-3));
    int i = std::floor(number);
    float realU = number-i;
    return valueParametric(i, realU);
}

const int SIZE_OF_STRIP_POINT = 6;

void BSpline_old::populatePointsVector(uint pointsCount) {
    int pointCount = pointsCount;
    auto *data = new float[SIZE_OF_STRIP_POINT * pointCount];

    for(int i = 0; i < pointCount; ++i) {
        float u = (float)i / (float)(pointCount-1);
        glm::vec3 point = valueParametric(u);
        data[i*6+0] = point.x;
        data[i*6+1] = point.y;
        data[i*6+2] = point.z;
        data[i*6+3] = (float)i / (float)pointCount;
        data[i*6+4] = (float)i / (float)pointCount;
        data[i*6+5] = 1.0f - (float)i / (float)pointCount;
    }
    mPoints = data;
    mPointsCount = pointCount;
}

void BSpline_old::swapKnots(int i1, int i2) {
    std::swap(mKnotVector[i1], mKnotVector[i2]);
}
