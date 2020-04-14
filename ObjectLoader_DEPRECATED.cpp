//
// Created by stef on 11.04.20.
//

#include "ObjectLoader_DEPRECATED.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Object_DEPRECATED.h"


//Object_DEPRECATED *ObjectLoader_DEPRECATED::loadModel(std::string filepath) {
//    Assimp::Importer import;
//    const aiScene *scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
//    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
//        return nullptr;
//    }
//    auto directory = filepath.substr(0, filepath.find_last_of('/'));
//
//    processNode(scene->mRootNode, scene);
//
////    return nullptr;
//}
//
//
//void ObjectLoader_DEPRECATED::processNode(aiNode *node, const aiScene *scene) {
//    // process all the node's meshes (if any)
//    for(unsigned int i = 0; i < node->mNumMeshes; i++)
//    {
//        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//        mMeshes.push_back(processMesh(mesh, scene));
//    }
//    // then do the same for each of its children
//    for(unsigned int i = 0; i < node->mNumChildren; i++)
//    {
//        processNode(node->mChildren[i], scene);
//    }
//}
//
//Mesh ObjectLoader_DEPRECATED::processMesh(aiMesh *mesh, const aiScene *scene) {
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//
//    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
//    {
//        Vertex vertex;
//        // process vertex positions, normals and texture coordinates
//        vertex.Position.x = mesh->mVertices[i].x;
//        vertex.Position.y = mesh->mVertices[i].y;
//        vertex.Position.z = mesh->mVertices[i].z;
//        vertex.Normal.x = mesh->mNormals[i].x;
//        vertex.Normal.y = mesh->mNormals[i].y;
//        vertex.Normal.z = mesh->mNormals[i].z;
//        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
//        {
//            vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
//            vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
//        }
//        else
//            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//        vertices.push_back(vertex);
//    }
//    // process indices
//    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
//    {
//        aiFace face = mesh->mFaces[i];
//        for(unsigned int j = 0; j < face.mNumIndices; j++)
//            indices.push_back(face.mIndices[j]);
//    }
//    // process material
//    if(mesh->mMaterialIndex >= 0)
//    {
//        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
//        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//    }
//
//    return {vertices, indices, textures};
//}
//
//std::vector<Texture> ObjectLoader_DEPRECATED::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
//    std::vector<Texture> textures;
//    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//    {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//        Texture texture;
////        texture.id = TextureFromFile(str.C_Str(), directory);
//        texture.type = typeName;
////        texture.path = str;
//        textures.push_back(texture);
//    }
//    return textures;
//}
