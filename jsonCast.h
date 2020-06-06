//
// Created by stef on 23.05.20.
//

#ifndef PROJECT_JSON_CAST_H
#define PROJECT_JSON_CAST_H

#include <glm/vec3.hpp>
#include "vendor/nlohmann/json.hpp"

class FFD;
class Keyframe;
class CSkeleton;
class CJoint;
class CLink;
class Plant;

namespace glm {
    void to_json(nlohmann::json& j, const glm::vec3& p);
    void from_json(const nlohmann::json& j, glm::vec3& p);
}

// ffd
void to_json(nlohmann::json &j, const FFD &ffd);
// keyframe
void from_json(const nlohmann::json &j, Keyframe &kf);
// skeletons
void to_json(nlohmann::json &j, const CSkeleton &skeleton);
void to_json(nlohmann::json &j, const CJoint &joint);
void to_json(nlohmann::json &j, const CLink &link);
// plant
void to_json(nlohmann::json &j, const Plant &plant);

#endif