//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_PATH_H
#define PROJECT_PATH_H


#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <list>
#include "Orientation.h"

class Keyframe;

class Path {
public:
    virtual void addKeyframe(Keyframe keyframe) = 0;
    virtual bool hasKeyframe(uint frameindex) = 0;
    virtual std::list<Keyframe>* getKeyFrames() = 0;
    virtual Orientation orientation(int frameIndex) = 0;
};


#endif //PROJECT_PATH_H
