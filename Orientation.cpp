//
// Created by stef on 10.04.20.
//

#include "Orientation.h"

Orientation::Orientation(glm::vec3 position, glm::quat rotation, glm::vec3 scale) :
    position(position),
    rotation(rotation),
    scale(scale)
{
}

Orientation::Orientation(Keyframe &keyframe)  :
    position(keyframe.getPos()),
    rotation(keyframe.getRot()),
    scale(keyframe.getScale())
{
}
