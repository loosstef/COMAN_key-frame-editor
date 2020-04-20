//
// Created by stef on 11.04.20.
//

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "FFD.h"

Model::Model(char *path) {
    loadModel(path);
}

void Model::Draw(int frameIndex, GLint uniTexture) {
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(frameIndex, uniTexture);
//    for(int i = 0; i < all_frameIndices.size(); ++i) {
//        if(all_frameIndices[i] == frameIndex) {
//            all_ffds[i]->renderControlPoints()
//        }
//    }
}


void Model::loadModel(std::string path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // process vertex positions, normals and texture coordinates
        glm::vec3 &position = vertices[i].Position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        glm::vec3 &normal = vertices[i].Normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        glm::vec2 &texCoord = vertices[i].TexCoords;
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            texCoord.x = mesh->mTextureCoords[0][i].x;
            texCoord.y = mesh->mTextureCoords[0][i].y;
        }
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory, false);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma) {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

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
        std::cout << "Texture failed to load at path: " << filename << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Model::getModelDimensions(glm::vec3 &P0, glm::vec3 &S, glm::vec3 &T, glm::vec3 &U) {
//    P0.x = meshes[0].curr_vertices[0].Position.x;
    P0.x = meshes[0].getOrigVertices()[0].Position.x;
//    P0.y = meshes[0].curr_vertices[0].Position.y;
    P0.y = meshes[0].getOrigVertices()[0].Position.y;
//    P0.z = meshes[0].curr_vertices[0].Position.z;
    P0.z = meshes[0].getOrigVertices()[0].Position.z;
    // calculate P0
    for(int i = 0; i < meshes.size(); ++i) {
        Mesh &mesh = meshes[i];
        for(int j = 0; j < /*mesh.curr_vertices.size()*/ mesh.getOrigVertices().size(); ++j) {
            Vertex &vertex = mesh.getOrigVertices()[j];
//            Vertex &vertex = mesh.curr_vertices[j];
            if(vertex.Position.x < P0.x)
                P0.x = vertex.Position.x;
            if(vertex.Position.y < P0.y)
                P0.y = vertex.Position.y;
            if(vertex.Position.z < P0.z)
                P0.z = vertex.Position.z;
        }
    }
    // calculate S, T and U
    float deltaX = 0;
    float deltaY = 0;
    float deltaZ = 0;
    for(int i = 0; i < meshes.size(); ++i) {
        Mesh &mesh = meshes[i];
        for (int j = 0; j < /*mesh.curr_vertices.size()*/mesh.getOrigVertices().size(); ++j) {
            Vertex &vertex = mesh.getOrigVertices()[j];
//            Vertex &vertex = mesh.curr_vertices[j];
            if((vertex.Position.x - P0.x) > deltaX)
                deltaX = vertex.Position.x - P0.x;
            if((vertex.Position.y - P0.y) > deltaY)
                deltaY = vertex.Position.y - P0.y;
            if((vertex.Position.z - P0.z) > deltaZ)
                deltaZ = vertex.Position.z - P0.z;
        }
    }
    S.x = deltaX;
    S.y = 0;
    S.z = 0;
    T.x = 0;
    T.y = deltaY;
    T.z = 0;
    U.x = 0;
    U.y = 0;
    U.z = deltaZ;
}

void Model::applyFFD(int frameIndex, FFD *ffd) {
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].applyFFD(frameIndex, *ffd);
    all_ffds.push_back(ffd);
    all_frameIndices.push_back(frameIndex);
}

//void Model::setFFD(FFD *ffd) {
//    for(unsigned int i = 0; i < meshes.size(); i++)
//        meshes[i].setFFD(ffd);
//}
