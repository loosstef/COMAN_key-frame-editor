//
// Created by stef on 05.05.20.
//

#ifndef PROJECT_PLANT_H
#define PROJECT_PLANT_H

#include <vector>
#include <string>
#include "StandardShader.h"
#include "vendor/nlohmann/json.hpp"

class Branch;
class RenderEngine;

class Plant {
public:
    Plant(std::string structure);
    explicit Plant(nlohmann::json &j);
    ~Plant();
    void draw(RenderEngine &re, StandardShader &shader);
    [[nodiscard]] std::string getStructure() const { return mStructure; }
private:
    Branch *mRoot;
    std::string mStructure;
};


#endif //PROJECT_PLANT_H
