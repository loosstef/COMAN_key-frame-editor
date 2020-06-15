//
// Created by stef on 11.04.20.
//

#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H


#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"


class Model {
public:
    /*  Functions   */
    Model(char *path);
    void draw(int frameIndex, GLint uniTexture);
    void getModelDimensions(glm::vec3 &P0, glm::vec3 &S, glm::vec3 &T, glm::vec3 &U);
    void applyFFD(int frameIndex, FFD *ffd);
    void removeFFD(int frameIndex);
    [[nodiscard]] std::string getPath() const { return mPath; }
    void onFFDChange();
private:
    /*  Model Data  */
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
    std::string mPath;
    /*  Functions   */
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
};


#endif //PROJECT_MODEL_H
