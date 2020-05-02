//
// Created by stef on 21.04.20.
//

#include <GL/glew.h>
#include <iostream>
#include "Mouse3D.h"
#include "Scene.h"
#include "StepAheadAnimationChannel.h"
#include "RenderEngine.h"
#include "Camera.h"

void Mouse3D::mouse_button_callback(GLFWwindow *window, int button, int action, int mods, Scene &scene) {
    // set mouse state variables
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS)
            lMouseBtnDown = true;
        else if(action == GLFW_RELEASE)
            lMouseBtnDown = false;
    }
    // detect clicked location
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double currMousePosX, currMousePosY;
        glfwGetCursorPos(window, &currMousePosX, &currMousePosY);
        RenderEngine &renderEngine = scene.getRenderEngine();
        Clock *clock = scene.getClock();
//        picked = renderEngine.pick_DEPRECATED(clock->getFrameIndex(), currMousePosX, currMousePosY, window);
        picked = renderEngine.pick(scene, currMousePosX, currMousePosY, window);
        mouseWindowCoord = glm::vec2(currMousePosX, currMousePosY);
        // TODO: calculate 3d mouse coordinate
        if(picked.channel == nullptr) {
            return;
        }
        if(picked.channel->getType() == SAA && picked.ffd != nullptr) {
            StepAheadAnimationChannel *pickedSaaChannel = (StepAheadAnimationChannel*)picked.channel;
            int windowHeight = scene.getRenderEngine().getWindowHeight();
            glm::vec3 localAbsPosCtrlPoint = picked.ffd->getLocalAbsoluteLoc(picked.controlPointIndex);
            glm::mat4 viewMat = scene.getRenderEngine().getEditorCamera().getViewMatrix();
            glm::mat4 modelMat = pickedSaaChannel->getTransMat();
            glm::mat4 modelViewMat = viewMat * modelMat;
            glm::mat4 projMat = scene.getRenderEngine().getProjectionMatrix();
            int width = scene.getRenderEngine().getWindowWidth();
            int height = scene.getRenderEngine().getWindowHeight();
            glm::vec4 viewport(0.0f, 0.0f, width, height);
            glm::vec3 mouseWindowPos = glm::project(localAbsPosCtrlPoint, modelViewMat, projMat, viewport);
            mouseWindowZ = mouseWindowPos.z;
            mouseSceneCoord = glm::unProject(glm::vec3(mouseWindowPos.x, (float)windowHeight-mouseWindowPos.y, mouseWindowZ), modelViewMat, projMat, viewport);
//            picked.ffd->setControlPoint(picked.controlPointIndex, mouseSceneCoord);
            picked.ffd->setControlPointAbsCoord(picked.controlPointIndex, mouseSceneCoord);
            std::cout << mouseWindowCoord.y << std::endl;
        }

    }
}

void Mouse3D::loop(Scene &scene, double mouseX, double mouseY) {
    if(lMouseBtnDown && picked.ffd != nullptr) {
        StepAheadAnimationChannel *pickedSaaChannel = (StepAheadAnimationChannel*)picked.channel;
        glm::mat4 viewMat = scene.getRenderEngine().getEditorCamera().getViewMatrix();
        glm::mat4 modelMat = (pickedSaaChannel)->getTransMat();
        glm::mat4 modelViewMat = viewMat * modelMat;
        glm::mat4 projMat = scene.getRenderEngine().getProjectionMatrix();
        int width = scene.getRenderEngine().getWindowWidth();
        int height = scene.getRenderEngine().getWindowHeight();
        glm::vec4 viewport(0.0f, 0.0f, width, height);
        float windowHeight = scene.getRenderEngine().getWindowHeight();
        mouseSceneCoord = glm::unProject(glm::vec3(mouseX, windowHeight-mouseY, mouseWindowZ), modelViewMat, projMat, viewport);
        picked.ffd->setControlPointAbsCoord(picked.controlPointIndex, mouseSceneCoord);
        pickedSaaChannel->tellModelFFDChanged(picked.ffd, scene.getClock()->getFrameIndex());
    }
}
