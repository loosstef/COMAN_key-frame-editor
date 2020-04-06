//
// Created by stef on 02.03.20.
//

#include <fstream>
#include <iostream>
#include "InputHandler.h"

void InputHandler::loadFile(char *fileName, std::string &content) {
    content.clear();
    std::ifstream shaderFile(fileName);
    std::string line;
    if(shaderFile.is_open()) {
        while(getline(shaderFile, line)) {
            content.append(line);
            content.append("\n");
        }
        shaderFile.close();
    }
    else {
        std::cerr << "Error while loading shader. File '" << fileName << "' was not found in build directory.";
    }
}

/**
 * Load a shader from a given file and compile it.
 * @param fileName
 * @param shaderType
 * @return GLuint reference to shader
 */
GLuint InputHandler::loadAndCompileShader(char *fileName, GLenum shaderType) {
    std::string shaderCode;
    loadFile(fileName, shaderCode);
    GLuint shader = glCreateShader(shaderType);
    const char *shaderCharPointer = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderCharPointer, NULL);
    glCompileShader(shader);
    return shader;
}


glm::vec3 InputHandler::readMoveButtons(GLFWwindow* window, float moveSpeed) {
    glm::vec3 movement(0.0f);
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
        movement += glm::vec3(-moveSpeed, 0.0f, 0.0f);
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
        movement += glm::vec3(moveSpeed, 0.0f, 0.0f);
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
        movement += glm::vec3(0.0f, 0.0f, moveSpeed);
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
        movement += glm::vec3(0.0f, 0.0f, -moveSpeed);
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) {
        movement += (glm::vec3(0.0f, -moveSpeed, 0.0f));
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
        movement += (glm::vec3(0.0f, moveSpeed, 0.0f));
    }
    return movement;
}