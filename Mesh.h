//
// Created by stef on 11.04.20.
//

#ifndef PROJECT_MESH_H
#define PROJECT_MESH_H


#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

class FFD;

struct Vertex {
    Vertex(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 norm = glm::vec3(0.0f), glm::vec2 texCoords = glm::vec2(0.0f)) : Position(pos), Normal(norm), TexCoords(texCoords) {}
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    /*  Mesh Data  */
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /* ffd */
    std::vector<Vertex> deformed_vertices;
    /*  Functions  */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(int frameIndex, GLint uniTexture);
    std::vector<Vertex>& getOrigVertices() { return orig_vertices; }
    void applyFFD(int frameIndex, FFD &ffd);
    void removeFFD(int frameIndex);
    void setTime(int frameIndex, bool checkChanged = true);
    void onFFDChange();
private:
    /*  Render data  */
    unsigned int VAO, VBO, EBO;
    /* time dependant data */
    std::vector<Vertex> orig_vertices;
    std::vector<Vertex> *curr_vertices = nullptr;
    std::vector<std::vector<Vertex>> all_vertices;
    std::vector<std::vector<Vertex>> generated_vertices;
    std::vector<int> generated_keyframeIndices;
    std::vector<int> keyframeIndices;
    int currentFrameIndex = 0;
    /*  Functions    */
    void setupMesh(std::vector<Vertex> &vertices);
};


#endif //PROJECT_MESH_H
