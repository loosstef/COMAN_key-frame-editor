//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_LINEARPATH_H
#define PROJECT_LINEARPATH_H

#include <list>
#include "Path.h"

class LinearPath : public Path {
public:
    void addKeyframe(Keyframe newKeyframe) override;
    bool hasKeyframe(uint frameIndex) override;
    std::list<Keyframe>* getKeyFrames() override { return &mKeyframes; }
    Orientation orientation(int frameIndex) override;
    // DEPRECATED FUNCTIONS
    Keyframe getKeyframe_DEPRECATED(uint frameIndex) override;
private:
    glm::vec3 linearInterpolate(glm::vec3 &vec1, glm::vec3 &vec2, float factor);
    glm::quat linearInterpolateRotation(glm::vec3 &rot1, glm::vec3 &rot2, float factor);
    std::list<Keyframe> mKeyframes;
};


#endif //PROJECT_LINEARPATH_H
