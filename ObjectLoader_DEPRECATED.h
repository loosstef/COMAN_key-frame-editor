//
// Created by stef on 11.04.20.
//

#ifndef PROJECT_OBJECTLOADER_DEPRECATED_H
#define PROJECT_OBJECTLOADER_DEPRECATED_H

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <assimp/material.h>

class Object_DEPRECATED;
class aiNode;
class aiScene;
class aiMesh;

//struct Vertex {
//    glm::vec3 Position;
//    glm::vec3 Normal;
//    glm::vec2 TexCoords;
//};
//
//struct Texture {
//    unsigned int id;
//    std::string type;
//};
//
//struct Mesh {
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//};

//class ObjectLoader_DEPRECATED {
//public:
//    Object_DEPRECATED* loadModel(std::string filepath);
//private:
//    void processNode(aiNode *node, const aiScene *scene);
//    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
//    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
//
//    std::vector<float> mNodes;
//    std::vector<Mesh> mMeshes;
//};


#endif //PROJECT_OBJECTLOADER_DEPRECATED_H
