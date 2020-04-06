//
// Created by stef on 03.03.20.
//

#ifndef ANTONGERDELAN_PATH_H
#define ANTONGERDELAN_PATH_H


#include <vector>
#include "../Object.h"

class Path_old : public Object {
public:
    Path_old(float* points = nullptr, int pointsCount = 0, GLenum mode = GL_LINE_STRIP);
    virtual glm::vec3 valueParametric(float u) = 0;
    glm::vec3 valueArcLength(float g);
    void populateArcLengthTable(uint stepCount);
private:
    float dist(glm::vec3 v1, glm::vec3 v2);
    uint locateClosestArcLength(float arcLength);
    std::vector<float> mArcLengthTable;
    float mTableStepSize;
};


#endif //ANTONGERDELAN_PATH_H
