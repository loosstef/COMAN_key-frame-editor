//
// Created by stef on 16.05.20.
//

#ifndef PROJECT_BSPLINEPATH_H
#define PROJECT_BSPLINEPATH_H


#include <vector>
#include <glm/detail/type_mat.hpp>
#include <map>

class BSpline;

class BSplinePath {
public:
    void add(BSpline *bSpline, std::pair<int,int> range);
    void add(glm::vec3 rotation, int frameIndex);
    glm::mat4 orientation(int frameIndex);
private:
    glm::vec3 calcPos(int frameIndex);
    glm::quat calcRot(int frameIndex);
    glm::quat linearInterpolateRotation(glm::vec3 &rot1, glm::vec3 &rot2, float factor);
    std::vector<BSpline*> mBSplines;
    std::vector<std::pair<int, int>> mIndexRanges;
    std::map<int, glm::vec3> mRotations;
};


#endif //PROJECT_BSPLINEPATH_H
