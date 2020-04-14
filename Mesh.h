//
// Created by stef on 11.04.20.
//

#ifndef PROJECT_MESH_H
#define PROJECT_MESH_H


#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

struct Vertex {
    Vertex(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 norm = glm::vec3(0.0f)) : Position(pos), Normal(norm) {}
    glm::vec3 Position;
    glm::vec3 Normal;
//    glm::vec2 TexCoords;
};

//struct Texture {
//    unsigned int id;
//    std::string type;
//};

class Mesh {
public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
    /*  Functions  */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices/*, std::vector<Texture> textures*/);
    void Draw(/*Shader shader*/);
private:
    /*  Render data  */
    unsigned int VAO, VBO, EBO;
    /*  Functions    */
    void setupMesh();
};


#endif //PROJECT_MESH_H
