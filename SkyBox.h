//
// Created by stef on 11.05.20.
//

#ifndef PROJECT_SKYBOX_H
#define PROJECT_SKYBOX_H

#include <string>
#include <vector>
#include "Scene.h"

class SkyBox {
public:
    SkyBox(std::vector<std::string> faces);
    void draw(Scene &scene);
private:
    unsigned int mVAO;
    unsigned int mTextureID;
    // functions
    static unsigned int loadCubemap(std::vector<std::string> faces);
    unsigned int loadToGPU(std::vector<float> &vertices);
};


#endif //PROJECT_SKYBOX_H
