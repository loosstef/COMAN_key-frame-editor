//
// Created by stef on 16.05.20.
//

#ifndef PROJECT_BSPLINE_H
#define PROJECT_BSPLINE_H


#include <glm/vec3.hpp>
#include <vector>
#include <GL/glew.h>

class Scene;

class BSpline {
public:
    // constructor
    BSpline(glm::vec3 pBegin, std::vector<glm::vec3> otherKnots, glm::vec3 pEnd);
    // knot-manipulation
    void add(glm::vec3 knot);
    void add(int index, glm::vec3 knot);
    void swapKnots(int i1, int i2);
    // get point on curve
    glm::vec3 valueParametric(int i, float u);
    glm::vec3 valueParametric(float u);
    glm::vec3 valueArcLength(float g);
    // init data
    void populatePointsVector(uint pointsCount);
    void populateArcLengthTable(uint stepCount);
    // drawing
    void loadToGPU(int pointsLayout = 0);
    void draw(Scene &scene);

private:
    // functionality
    float dist(glm::vec3 v1, glm::vec3 v2);
    uint locateClosestArcLength(float arcLength);
    // drawing
    GLuint mVAO, mVBO;
    float *mPoints;
    int mPointsCount;
    // knots
    std::vector<glm::vec3> mKnotVector;
    std::vector<float> mArcLengthTable;
    float mTableStepSize;
    // local constants
    const float MATRIX_ARRAY[16] = {-1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0};
    glm::mat4 MATRIX = glm::mat4(-1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0);
    const int SIZE_OF_STRIP_POINT = 6;
};


#endif //PROJECT_BSPLINE_H
