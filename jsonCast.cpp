//
// Created by stef on 23.05.20.
//


#include "jsonCast.h"
#include "FFD.h"
#include "Keyframe.h"
#include "CSkeleton.h"
#include "CLink.h"
#include "CJoint.h"
#include "Plant.h"


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


void from_json(const nlohmann::json &j, Keyframe &kf) {
    int frameIndex = j["frame_index"].get<int>();
    glm::vec3 pos = j["position"];
    glm::vec3 rot = j["rotation"];
    glm::vec3 scale = j["scale"];
    kf.setFrameIndex(frameIndex);
    kf.setPos(pos);
    kf.setRot(rot);
    kf.setScale(scale);
}


void to_json(nlohmann::json &j, const CSkeleton &skeleton) {
    j["root_joint"] = *skeleton.getRootJoint();
}


void to_json(nlohmann::json &j, const CJoint &joint) {
    j["id"] = joint.getId();
    j["link_offset"] = joint.offset();
    j["joint_angle"] = joint.currJointAngle();
    j["joint_angles"] = joint.jointAngles();
    j["frame_indices"] = joint.frameIndices();
    j["min_joint_angle"] = joint.minJointangle();
    j["max_joint_angle"] = joint.maxJointAngle();
    j["max_children_count"] = joint.maxChildrenCount();
    std::vector<CLink*> childLinks = joint.childLinks();
    for(auto *childLink : childLinks) {
        j["child_links"].push_back(*childLink);
    }
}


void to_json(nlohmann::json &j, const CLink &link) {
    j["link_length"] = link.linkLength();
    j["link_twist"] = link.linkTwist();
    j["second_point"] = link.getSecondPoint();
    j["child_joint"] = *link.getChildJoint();
}

void to_json(nlohmann::json &j, const Plant &plant) {
    j["structure"] = plant.getStructure();
}
