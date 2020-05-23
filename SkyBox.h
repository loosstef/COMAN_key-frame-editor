//
// Created by stef on 11.05.20.
//

#ifndef PROJECT_SKYBOX_H
#define PROJECT_SKYBOX_H

#include <string>
#include <vector>
#include "Scene.h"
#include "vendor/nlohmann/json.hpp"

class SkyBox {
public:
    SkyBox(std::vector<std::string> faces);
    explicit SkyBox(nlohmann::json j);
    void draw(Scene &scene);
    // saving
    nlohmann::json to_json();
private:
    unsigned int mVAO;
    unsigned int mTextureID;
    // initialization
    void init(std::vector<std::string> faces);
    // extra data
    std::vector<std::string> mFaces;
    // functions
    static unsigned int loadCubemap(std::vector<std::string> faces);
    unsigned int loadToGPU(std::vector<float> &vertices);
};


#endif //PROJECT_SKYBOX_H
