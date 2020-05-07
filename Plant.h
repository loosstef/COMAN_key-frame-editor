//
// Created by stef on 05.05.20.
//

#ifndef PROJECT_PLANT_H
#define PROJECT_PLANT_H

#include <vector>
#include <string>
#include "StandardShader.h"

class Branch;
class RenderEngine;

class Plant {
public:
    Plant(std::string structure);
    ~Plant();
    void draw(RenderEngine &re, StandardShader &shader);
private:
    Branch *mRoot;
};


#endif //PROJECT_PLANT_H
