//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_LINEARPATH_H
#define PROJECT_LINEARPATH_H

#include <list>
#include "Path.h"

class LinearPath : public Path {
public:
    void addKeyframe(Keyframe newKeyframe);
    bool hasKeyframe(uint frameIndex);
    Keyframe getKeyframe(uint frameIndex);
private:
    std::list<Keyframe> mKeyframes;
};


#endif //PROJECT_LINEARPATH_H
