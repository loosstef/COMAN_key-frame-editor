//
// Created by stef on 21.04.20.
//

#ifndef PROJECT_MOUSE3D_H
#define PROJECT_MOUSE3D_H

#include <GLFW/glfw3.h>
#include "Picked.cpp"

class Scene;

class Mouse3D {
public:
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods, Scene &scene);
    Picked picked;
private:
    bool lMouseBtnDown = false;
    glm::vec2 mouseWindowCoord;
    glm::vec3 mouseSceneCoord;
};


#endif //PROJECT_MOUSE3D_H
