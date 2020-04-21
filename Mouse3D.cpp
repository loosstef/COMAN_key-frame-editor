//
// Created by stef on 21.04.20.
//

#include <GL/glew.h>
#include "Mouse3D.h"
#include "Scene.h"

void Mouse3D::mouse_button_callback(GLFWwindow *window, int button, int action, int mods, Scene &scene) {
    // set mouse state variables
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS)
            lMouseBtnDown = true;
        else if(action == GLFW_RELEASE)
            lMouseBtnDown = false;
    }
    // detect clicked location
    double currMousePosX, currMousePosY;
    glfwGetCursorPos(window, &currMousePosX, &currMousePosY);
    RenderEngine *renderEngine = scene.getRenderEngine();
    Clock *clock = scene.getClock();
    picked = renderEngine->pick(clock->getFrameIndex(), currMousePosX, currMousePosY, window);
    mouseWindowCoord = glm::vec2(currMousePosX, currMousePosY);
    // TODO: calculate 3d mouse coordinate
}
