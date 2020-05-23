//
// Created by stef on 21.04.20.
//

#ifndef PROJECT_MOUSE3D_H
#define PROJECT_MOUSE3D_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Picked.h"

class Scene;

class Mouse3D {
public:
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods, Scene &scene);
    void loop(Scene &scene, double mouseX, double mouseY);
    Picked picked;
private:
    bool lMouseBtnDown = false;
    glm::vec2 mouseWindowCoord;
    glm::vec3 mouseSceneCoord;
    double mouseWindowZ;
};


#endif //PROJECT_MOUSE3D_H
