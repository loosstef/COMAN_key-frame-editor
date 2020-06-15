//
// Created by stef on 10.04.20.
//

#ifndef PROJECT_ORIENTATION_H
#define PROJECT_ORIENTATION_H

#include <glm/vec3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Keyframe.h"

class Orientation {
public:
    Orientation(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0f));
    explicit Orientation(Keyframe &keyframe);
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};


#endif //PROJECT_ORIENTATION_H
