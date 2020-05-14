//
// Created by stef on 11.05.20.
//

#ifndef PROJECT_SKYBOX_DEPRECATED_H
#define PROJECT_SKYBOX_DEPRECATED_H

#include <string>
#include <GL/glew.h>
#include "../Mesh.h"

class SkyBox_DEPRECATED {
public:
    SkyBox_DEPRECATED(std::string front, std::string top, std::string left, std::string right, std::string bottom, std::string back);
private:
    unsigned int TextureFromFile(const std::string &path);
    void setupMesh();
    Vertex* genVertices();
    // paths of skybox textures
    std::string mFrontImgPath;
    std::string mTopImgPath;
    std::string mLeftImgPath;
    std::string mRightImgPath;
    std::string mBottomImgPath;
    std::string mBackImgPath;
    // texture id's
    GLint mFrontId, mTopId, mLeftId, mRightId, mBottomId, mBackId;
    // VAO's
//    unsigned int mVaoFront, mVaoTop, mVaoLeft, mVaoRight, mVaoBottom, mVaoBack;
    unsigned int mVao[6];

};


#endif //PROJECT_SKYBOX_DEPRECATED_H
