//
// Created by stef on 23.05.20.
//


#include "jsonCast.h"
#include "FFD.h"


namespace glm {
    void to_json(nlohmann::json& j, const glm::vec3& p) {
        j = {p.x, p.y, p.z};
    }
    void from_json(const nlohmann::json& j, glm::vec3& p) {
        p.x = j[0];
        p.y = j[1];
        p.z = j[2];
    }
};


void to_json(nlohmann::json &j, const FFD &ffd) {
    j["P0"] = ffd.getP0();
    j["S"] = ffd.getS();
    j["T"] = ffd.getT();
    j["U"] = ffd.getU();
    j["control_points"] = ffd.getControlPointsJson();
}

void from_json(const nlohmann::json &j, FFD &ffd) {
    ffd.init(j);
}
