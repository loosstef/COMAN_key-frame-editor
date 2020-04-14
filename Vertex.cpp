//
// Created by stef on 14.04.20.
//

#include <glm/vec3.hpp>

struct Vertex {
    Vertex(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 norm = glm::vec3(0.0f)) : Position(pos), Normal(norm) {}
    glm::vec3 Position;
    glm::vec3 Normal;
//    glm::vec2 TexCoords;
};