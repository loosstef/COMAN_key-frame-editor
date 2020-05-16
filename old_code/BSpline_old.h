//
// Created by stef on 26.02.20.
//

#ifndef ANTONGERDELAN_BSPLINE_H
#define ANTONGERDELAN_BSPLINE_H

#include <glm/glm.hpp>
#include <vector>
#include "Object_DEPRECATED.h"
#include "Path_old.h"


class BSpline_old : public Path_old {
public:
    BSpline_old(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);
    BSpline_old(glm::vec3 pBegin, std::vector<glm::vec3> otherKnots, glm::vec3 pEnd);
    void add(glm::vec3 knot);
    void add(int index, glm::vec3 knot);
    void swapKnots(int i1, int i2);
    glm::vec3 valueParametric(int i, float u);
    glm::vec3 valueParametric(float u);
    void populatePointsVector(uint pointsCount);
private:
    std::vector<glm::vec3> mKnotVector;
};


#endif //ANTONGERDELAN_BSPLINE_H
