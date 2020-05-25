//
// Created by stef on 23.05.20.
//

#ifndef PROJECT_JSON_CAST_H
#define PROJECT_JSON_CAST_H

#include <glm/vec3.hpp>
#include "vendor/nlohmann/json.hpp"

class FFD;

namespace glm {
    void to_json(nlohmann::json& j, const glm::vec3& p);
    void from_json(const nlohmann::json& j, glm::vec3& p);
}

void to_json(nlohmann::json &j, const FFD &ffd);
void from_json(const nlohmann::json &j, FFD &ffd);

#endif