//
// Created by stef on 11.04.20.
//

#include "Mesh.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "FFD.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
        orig_vertices(vertices), indices(indices), textures(textures)
{
    curr_vertices = &orig_vertices;
//    all_vertices[0] = vertices;
//    curr_vertices = &all_vertices[0];
//    this->vertices = vertices;
//    this->indices = indices;
//    this->textures = textures;
    setupMesh(*curr_vertices);
}

void Mesh::setupMesh(std::vector<Vertex> &vertices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(int frameIndex, GLint uniTexture) {
    setTime(frameIndex);

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

//        shader.setFloat(("material." + name + number).c_str(), i);
        glUniform1f(uniTexture, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // FFD ZOOI
//    if(ffd != nullptr) {
//        deformed_vertices = ffd->calcPos_debug(frameIndex, orig_vertices);
//        setupMesh(deformed_vertices);
//    }
    // END OF FFD ZOOI

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);
}

void Mesh::applyFFD(int frameIndex, FFD &ffd) {
    keyframeIndices.push_back(frameIndex);
    all_vertices.emplace_back(ffd.calcPos_debug(orig_vertices));
    generated_keyframeIndices.clear();
    generated_vertices.clear();
}

/**
 * Set the current timestamp. The mesh will deform correctly (based on it's fFD)
 * It will calculate new vertices and load them to the GPU.
 * @param frameIndex
 */
void Mesh::setTime(int frameIndex) {
    if(currentFrameIndex == frameIndex)
        return;
    if(keyframeIndices.empty()) {
        curr_vertices = &orig_vertices;
        setupMesh(*curr_vertices);
        return;
    }
    if(keyframeIndices.size() == 1) {
        curr_vertices = &all_vertices[0];
        setupMesh(*curr_vertices);
        return;
    }
    currentFrameIndex = frameIndex;
    for(int i = 0; i < keyframeIndices.size(); ++i) {
        if(keyframeIndices[i] == frameIndex) {
            curr_vertices = &all_vertices[i];
            setupMesh(*curr_vertices);
            return;
        }
    }
    for(int i = 0; i < generated_keyframeIndices.size(); ++i) {
        if(generated_keyframeIndices[i] == frameIndex) {
            curr_vertices = &generated_vertices[i];
            setupMesh(*curr_vertices);
            return;
        }
    }
    int lowerIndex = -1;
    int lowerFrameIndex = -1;
    int higherIndex = -1;
    int higherFrameIndex = std::numeric_limits<int>::max();
    for(int i = 0; i < keyframeIndices.size(); ++i) {
        if(keyframeIndices[i] > lowerFrameIndex && keyframeIndices[i] < frameIndex) {
            lowerIndex = i;
            lowerFrameIndex = keyframeIndices[i];
        }
        else if(keyframeIndices[i] < higherFrameIndex && keyframeIndices[i] > frameIndex) {
            higherIndex = i;
            higherFrameIndex = keyframeIndices[i];
        }
    }
    if(lowerIndex == -1) {
        curr_vertices = &all_vertices[higherIndex];
        setupMesh(*curr_vertices);
        return;
    }
    if(higherIndex == -1) {
        curr_vertices = &all_vertices[lowerIndex];
        setupMesh(*curr_vertices);
        return;
    }
    // uitmiddelen
    std::vector<Vertex> nVertices;
    for(int i = 0; i < all_vertices[lowerIndex].size(); ++i) {
        Vertex &earlyVertex = all_vertices[lowerIndex][i];
        Vertex &laterVertex = all_vertices[higherIndex][i];
        float factor = (float)(frameIndex-lowerFrameIndex) / (float)(higherFrameIndex-lowerFrameIndex);
        glm::vec3 newPos = earlyVertex.Position + (factor * (laterVertex.Position-earlyVertex.Position));
        nVertices.emplace_back(newPos, earlyVertex.Normal, earlyVertex.TexCoords);
    }
    generated_vertices.push_back(nVertices);
    generated_keyframeIndices.push_back(frameIndex);
    curr_vertices = &generated_vertices[generated_vertices.size()-1];
    setupMesh(*curr_vertices);
}
