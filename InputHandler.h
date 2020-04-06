//
// Created by stef on 02.03.20.
//

#ifndef ANTONGERDELAN_INPUTHANDLER_H
#define ANTONGERDELAN_INPUTHANDLER_H


#include <string>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "RenderEngine.h"

const float MOUSE_SENSITIVITY_ROTATION = 0.08f;
const float MOUSE_SENSITIVITY_MOVEMENT = 0.005f;

class InputHandler {
public:
    InputHandler(GLFWwindow *window, RenderEngine *renderEngine);
    static void loadFile(char* fileName, std::string &content);
    static GLuint loadAndCompileShader(char* fileName, GLenum shaderType);
    static glm::vec3 readMoveButtons_DEPRECATED(GLFWwindow* window, float moveSpeed);
    void handleMouse();
private:
    GLFWwindow* window;
    RenderEngine* mRenderEngine;
    bool mRightMouseBtnWasDown = false;
    double mLastMousePosX = 0.0;
    double mLastMousePosY = 0.0;
};


#endif //ANTONGERDELAN_INPUTHANDLER_H
