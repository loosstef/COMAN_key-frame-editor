//
// Created by stef on 16.05.20.
//

#include <iostream>
#include <glm/detail/type_vec4.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x3.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "BSpline.h"
#include "Scene.h"


/**
 * Constructor
 * @param pBegin first knot
 * @param otherKnots other knots
 * @param pEnd last knot
 */
BSpline::BSpline(glm::vec3 pBegin, std::vector<glm::vec3> otherKnots, glm::vec3 pEnd) {
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

/**
 * Add a knot to the end of the knot-array
 * @param knot
 */
void BSpline::add(glm::vec3 knot) {
    mKnotVector.push_back(knot);
}

/**
 * Add a knot to a certain location in the knot-array
 * @param index
 * @param knot
 */
void BSpline::add(int index, glm::vec3 knot) {
    auto it = mKnotVector.begin()+index;
    mKnotVector.insert(it, knot);
}

/**
 * Swap 2 knots in the knot-vector
 * @param i1 index of first knot
 * @param i2 index of second knot
 */
void BSpline::swapKnots(int i1, int i2) {
    std::swap(mKnotVector[i1], mKnotVector[i2]);
}


glm::vec3 BSpline::valueParametric(int i, float u) {
    if(i > mKnotVector.size()-3 || i < 0) {
        std::cerr << "[error] BSpline, index out of bound." << std::endl;
        exit(1);
    }

    glm::vec4 weights = 1.0f / 6.0f * glm::vec4(u*u*u, u*u, u, 1.0f) * MATRIX;
    glm::mat4x3 pointMat(mKnotVector[i], mKnotVector[i+1], mKnotVector[i+2], mKnotVector[i+3]);
    return pointMat * weights;
}


glm::vec3 BSpline::valueParametric(float u) {
    int n = mKnotVector.size();
    if(u == 1) {
        return valueParametric(n - 4, 1);
    }
    float number = (u * (n-3));
    int i = std::floor(number);
    float realU = number-i;
    return valueParametric(i, realU);
}


glm::vec3 BSpline::valueArcLength(float g) {
    if(g == 1.0f) {
        return valueParametric(1.0f);
    }
    uint lowerIndex = locateClosestArcLength(g);
    uint higherIndex = lowerIndex+1;
    float lowerArcLength = mArcLengthTable[lowerIndex];
    float higherArcLength = mArcLengthTable[higherIndex];
    float lowerU = mTableStepSize * lowerIndex;
    float higherU = mTableStepSize * higherIndex;
    float factor = (g-lowerArcLength) / (higherArcLength-lowerArcLength);
    float u = lowerU + factor * (higherU-lowerU);
    return valueParametric(u);
}


void BSpline::populatePointsVector(uint pointsCount) {
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

float BSpline::dist(glm::vec3 v1, glm::vec3 v2) {
    return glm::distance(v1, v2);
}

uint BSpline::locateClosestArcLength(float arcLength) {
    int closestIndex;
    float closestArcDist = INFINITY;
    for(int i = 0; i < mArcLengthTable.size(); ++i) {
        float dist = arcLength - mArcLengthTable[i];
        if(dist < 0) {
            break;
        }
        if(dist < closestArcDist) {
            closestIndex = i;
            closestArcDist = dist;
        }
    }
    return closestIndex;
}

void BSpline::populateArcLengthTable(uint stepCount) {
    mTableStepSize = 1.0f / stepCount;
    float currArcLength = 0.0f;
    mArcLengthTable.push_back(currArcLength);
    glm::vec3 lastArcPoint = valueParametric(0.0f);
    for(int i = 1; i <= stepCount; ++i) {
        float u = (float)i / (float)stepCount;
        glm::vec3 currArcPoint = valueParametric(u);
        currArcLength += dist(lastArcPoint, currArcPoint);
        mArcLengthTable.push_back(currArcLength);
        lastArcPoint = currArcPoint;
    }
    // normalize all values
    for(int i = 1; i < stepCount; ++i) {
        mArcLengthTable[i] /= currArcLength;
    }
}

void BSpline::loadToGPU(int pointsLayout) {
    const int POINT_DATA_SIZE = 3;
    // generate vbo
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, POINT_DATA_SIZE * mPointsCount * sizeof(float), mPoints, GL_STATIC_DRAW);
    // generate vao
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(pointsLayout, POINT_DATA_SIZE, GL_FLOAT, GL_FALSE, POINT_DATA_SIZE*sizeof(float), NULL);
    glEnableVertexAttribArray(pointsLayout);
}

void BSpline::draw(Scene &scene) {
    Shader *shader = scene.renderEngine().shader();
    // check if using right shader
    if(shader->name().compare("standard") != 0) {
        std::cerr << "[error] Wrong shader set for drawing of the b-spline." << std::endl;
        return;
    }
    StandardShader *standardShader = (StandardShader*) shader;
    glBindVertexArray(mVAO);
    glm::mat4 standardTransMat(1.0f);
    standardShader->setMatrix(TRANSFORMATION_MATRIX, standardTransMat);
    glDrawArrays(GL_TRIANGLES, 0, mPointsCount);
}
