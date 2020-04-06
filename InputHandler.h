//
// Created by stef on 02.03.20.
//

#ifndef ANTONGERDELAN_INPUTHANDLER_H
#define ANTONGERDELAN_INPUTHANDLER_H


#include <string>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

class InputHandler {
public:
    static void loadFile(char* fileName, std::string &content);
    static GLuint loadAndCompileShader(char* fileName, GLenum shaderType);
    static glm::vec3 readMoveButtons(GLFWwindow* window, float moveSpeed);
};


#endif //ANTONGERDELAN_INPUTHANDLER_H
