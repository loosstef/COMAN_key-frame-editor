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
#include "CSkeleton.h"
#include "FFD.h"
#include "CJoint.h"

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
        RenderEngine &renderEngine = scene.renderEngine();
        Clock *clock = scene.clock();
//        picked = renderEngine.pick_DEPRECATED(clock->getFrameIndex(), currMousePosX, currMousePosY, window);
        picked = renderEngine.pick(scene, currMousePosX, currMousePosY, window);
        mouseWindowCoord = glm::vec2(currMousePosX, currMousePosY);
        if(picked.channel != nullptr && picked.channel->getType() == SAA && picked.ffd != nullptr) {
            StepAheadAnimationChannel *pickedSaaChannel = (StepAheadAnimationChannel*)picked.channel;
            int windowHeight = scene.renderEngine().getWindowHeight();
            glm::vec3 localAbsPosCtrlPoint = picked.ffd->getLocalAbsoluteLoc(picked.controlPointIndex);
            glm::mat4 viewMat = scene.renderEngine().editorCamera().getViewMatrix();
            glm::mat4 modelMat = pickedSaaChannel->getTransMat();
            glm::mat4 modelViewMat = viewMat * modelMat;
            glm::mat4 projMat = scene.renderEngine().camera().getProjectionMatrix();   //getProjectionMatrix();
            int width = scene.renderEngine().getWindowWidth();
            int height = scene.renderEngine().getWindowHeight();
            glm::vec4 viewport(0.0f, 0.0f, width, height);
            glm::vec3 mouseWindowPos = glm::project(localAbsPosCtrlPoint, modelViewMat, projMat, viewport);
            mouseWindowZ = mouseWindowPos.z;
        }
        else if(picked.joint != nullptr) {
            CJoint *joint = picked.joint;
            CSkeleton *skeleton = picked.skeleton;
            int windowHeight = scene.renderEngine().getWindowHeight();
            glm::vec3 localAbsPosCtrlPoint = joint->getGlobPos();
            glm::mat4 viewMat = scene.renderEngine().editorCamera().getViewMatrix();
            glm::mat4 modelViewMat = viewMat;
            glm::mat4 projMat = scene.renderEngine().camera().getProjectionMatrix();  // getProjectionMatrix();
            int width = scene.renderEngine().getWindowWidth();
            int height = scene.renderEngine().getWindowHeight();
            glm::vec4 viewport(0.0f, 0.0f, width, height);
            glm::vec3 mouseWindowPos = glm::project(localAbsPosCtrlPoint, modelViewMat, projMat, viewport);
            mouseWindowZ = mouseWindowPos.z;
        }
    }
}

void Mouse3D::loop(Scene &scene, double mouseX, double mouseY) {
    if(lMouseBtnDown && picked.ffd != nullptr) {
        StepAheadAnimationChannel *pickedSaaChannel = (StepAheadAnimationChannel*)picked.channel;
        glm::mat4 viewMat = scene.renderEngine().editorCamera().getViewMatrix();
        glm::mat4 modelMat = (pickedSaaChannel)->getTransMat();
        glm::mat4 modelViewMat = viewMat * modelMat;
        glm::mat4 projMat = scene.renderEngine().camera().getProjectionMatrix();  // getProjectionMatrix();
        int width = scene.renderEngine().getWindowWidth();
        int height = scene.renderEngine().getWindowHeight();
        glm::vec4 viewport(0.0f, 0.0f, width, height);
        float windowHeight = scene.renderEngine().getWindowHeight();
        mouseSceneCoord = glm::unProject(glm::vec3(mouseX, windowHeight-mouseY, mouseWindowZ), modelViewMat, projMat, viewport);
        picked.ffd->setControlPointAbsCoord(picked.controlPointIndex, mouseSceneCoord);
        pickedSaaChannel->tellModelFFDChanged(picked.ffd, scene.clock()->getFrameIndex());
    }
    if(lMouseBtnDown && picked.joint != nullptr) {
        CJoint *joint = picked.joint;
        CSkeleton *skeleton = picked.skeleton;
        int windowHeight = scene.renderEngine().getWindowHeight();
        glm::mat4 viewMat = scene.renderEngine().editorCamera().getViewMatrix();
        glm::mat4 modelViewMat = viewMat;
        glm::mat4 projMat = scene.renderEngine().camera().getProjectionMatrix();  // getProjectionMatrix();
        int width = scene.renderEngine().getWindowWidth();
        int height = scene.renderEngine().getWindowHeight();
        glm::vec4 viewport(0.0f, 0.0f, width, height);
        glm::vec3 localAbsPosCtrlPoint = joint->getGlobPos();
        glm::vec3 mouseWindowPos = glm::project(localAbsPosCtrlPoint, modelViewMat, projMat, viewport);
        mouseWindowZ = mouseWindowPos.z;
        mouseSceneCoord = glm::unProject(glm::vec3(mouseX, windowHeight-mouseY, mouseWindowZ), modelViewMat, projMat, viewport);
        skeleton->inverseKinematic(joint, mouseSceneCoord);
    }
}
