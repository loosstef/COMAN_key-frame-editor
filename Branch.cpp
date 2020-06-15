//
// Created by stef on 05.05.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Branch.h"
#include "RenderEngine.h"

Branch::Branch(std::string structure, glm::mat4 transMat, float length) : redDot("base_models/red_dot.obj") {
    mLength = length;
    mRotAngle = 0.44854961776f;
    mChildScale = 1.0f;
    if(length == 0.0f) {
        mChildScale = 1.0f;
    }
    // set drawing points
    mPoints[0] = glm::vec3(0.0f);
    // TODO: set length as y-value
    mPoints[1] = glm::vec3(0.0f, length, 0.0f);
    mIndices[0] = 0;
    mIndices[1] = 1;
    // set constructor variables
    mTransMat = transMat;
    // generate children based on given structure
    generate(structure, glm::mat4(1.0f));
    // load points to GPU
    setup();
}


void Branch::generate(std::string structure, glm::mat4 transMat) {
    // check if at end of structure
    if(structure.empty()) {
        return;
    }
    // work with next character from structure
    char nextChar = structure[0];
    if(nextChar == 'F' || nextChar == 'f') {
        glm::mat4 nextTransMat = glm::translate(mTransMat, glm::vec3(0.0f, mLength, 0.0f));
        nextTransMat = nextTransMat * transMat;
        nextTransMat = glm::scale(nextTransMat, glm::vec3(mChildScale));
        Branch nextBranch(structure.substr(1), nextTransMat);
        mChildren.push_back(nextBranch);
        return;
    }
    else if(nextChar == '+') {
        glm::mat4 nextTransMat = glm::rotate(transMat, mRotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        generate(structure.substr(1), nextTransMat);
        return;
    }
    else if(nextChar == '-') {
        glm::mat4 nextTransMat = glm::rotate(transMat, -mRotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        generate(structure.substr(1), nextTransMat);
        return;
    }
    else if(nextChar == 'R') {
        glm::mat4 nextTransMat = glm::rotate(transMat, mRotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        generate(structure.substr(1), nextTransMat);
        return;
    }
    else if(nextChar == 'r') {
        glm::mat4 nextTransMat = glm::rotate(transMat, -mRotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        generate(structure.substr(1), nextTransMat);
        return;
    }
    else if(nextChar == '[') {
        int closingBracketIndex = findClosingBracket(structure, 0);
        // generate left branch
        generate(structure.substr(1, closingBracketIndex-1), transMat);
        // generate right branch
        generate(structure.substr(closingBracketIndex+1), transMat);
    }
    else if(nextChar == ']') {
        std::cerr << "Error: Closing bracket found without matching opening bracket." << std::endl;
        exit(1);
    }
}

int Branch::findClosingBracket(std::string str, int openBracket) {
    int counter = 1;
    int index = openBracket;
    while(counter > 0) {
        ++index;
        if(str.size() <= index) {
            std::cerr << "Error: no closing bracket found." << std::endl;
            exit(1);
        }
        if(str[index] == ']') {
            --counter;
        }
        else if(str[index] == '[') {
            ++counter;
        }
    }
    return index;
}

void Branch::draw(RenderEngine &re, StandardShader &shader) {
    shader.setMatrix(TRANSFORMATION_MATRIX, mTransMat);
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);
    // draw children
    for(auto branch : mChildren) {
        branch.draw(re, shader);
    }
}

void Branch::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), &mPoints[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);
    glBindVertexArray(0);
}
