//
// Created by stef on 05.05.20.
//

#include "Plant.h"
#include "Branch.h"
#include "RenderEngine.h"

Plant::Plant(std::string structure) {
    mStructure = structure;
    if(structure[0] == 'F') {
        mRoot = new Branch(structure.substr(1), glm::mat4(1.0f));
    }
    else {
        mRoot = new Branch(structure, glm::mat4(1.0f), 0.0f);
    }
}

Plant::Plant(nlohmann::json &j) : Plant(j["structure"].get<std::string>()) {
}

Plant::~Plant() {
    delete mRoot;
}

void Plant::draw(RenderEngine &re, StandardShader &shader) {
    mRoot->draw(re, shader);
}
