//
// Created by stef on 11.05.20.
//

#include <iostream>
#include "SkyBox_DEPRECATED.h"
#include "../stb_image.h"
#include "../Mesh.h"

SkyBox_DEPRECATED::SkyBox_DEPRECATED(std::string front, std::string top, std::string left, std::string right, std::string bottom,
                                     std::string back)
{
    // set all paths
    mFrontImgPath = front;
    mTopImgPath = top;
    mLeftImgPath = left;
    mRightImgPath = right;
    mBottomImgPath = bottom;
    mBackImgPath = back;
    // load all textures and get id's
    mFrontId = TextureFromFile(front);
    mTopId = TextureFromFile(top);
    mLeftId = TextureFromFile(left);
    mRightId = TextureFromFile(right);
    mBottomId = TextureFromFile(bottom);
    mBackId = TextureFromFile(back);
}


unsigned int SkyBox_DEPRECATED::TextureFromFile(const std::string &path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else {
            std::cerr << "Error: number of components of texture was wrong read." << std::endl;
            exit(1);
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        exit(1);
    }

    return textureID;
}

void SkyBox_DEPRECATED::setupMesh() {
    glGenVertexArrays(6, mVao);
    unsigned int VBO[6];
    unsigned int EBO[6];
    glGenBuffers(6, VBO);
    glGenBuffers(6, EBO);
    Vertex vertices[4][6];
    for(int i = 0; i < 6; i++) {
        glBindVertexArray(mVao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    }
}

Vertex *SkyBox_DEPRECATED::genVertices() {
    Vertex vertices[4][6];
    vertices[0][0] = Vertex(glm::vec3(-1,-1,1));
}
