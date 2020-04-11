//
// Created by stef on 10.04.20.
//

#ifndef PROJECT_ORIENTATION_H
#define PROJECT_ORIENTATION_H

#include <glm/vec3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Orientation {
public:
    Orientation(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0f));
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};


#endif //PROJECT_ORIENTATION_H
