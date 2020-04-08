//
// Created by stef on 06.04.20.
//

#include <iostream>
#include "RenderEngine.h"
#include "Camera.h"
#include "StepAheadAnimationChannel.h"
#include "InputHandler.h"

char BASIC_VERTEX_SHADER_FILENAME[] = "shaders/simple_shader.vert";
char BASIC_FRAGMENT_SHADER_FILENAME[] = "shaders/simple_shader.frag";
char PICKING_VERTEX_SHADER_FILENAME[] = "shaders/color_picking_shader.vert";
char PICKING_FRAGMENT_SHADER_FILENAME[] = "shaders/color_picking_shader.frag";


RenderEngine::RenderEngine() {
    // load standard shaders
    GLuint vs = InputHandler::loadAndCompileShader(BASIC_VERTEX_SHADER_FILENAME, GL_VERTEX_SHADER);
    GLuint fs = InputHandler::loadAndCompileShader(BASIC_FRAGMENT_SHADER_FILENAME, GL_FRAGMENT_SHADER);
    mStandardShaderProgram = glCreateProgram();
    glAttachShader(mStandardShaderProgram, fs);
    glAttachShader(mStandardShaderProgram, vs);
    glLinkProgram(mStandardShaderProgram);
    glUseProgram(mStandardShaderProgram);
    mUniLocProjMat = glGetUniformLocation(mStandardShaderProgram, "projectionMatrix");
    mUniLocTransMat = glGetUniformLocation(mStandardShaderProgram, "modelMatrix");
    mUniLocViewMat = glGetUniformLocation(mStandardShaderProgram, "viewMatrix");
    mUniLocObjId = glGetUniformLocation(mStandardShaderProgram, "id");
    GLint standardId = 0;
    glUniform1i(mUniLocObjId, standardId);

    // create new camera
    mEditorCamera = new Camera();
    // generate and load projection matrix
    mProjectionMatrix = glm::perspective(
            glm::radians(45.0f),
            ((float)mWindowWidth) / ((float)mWindowHeight),
            CAMERA_NEAR_CLIPPING,
            CAMERA_FAR_CLIPPING
    );
    glUniformMatrix4fv(mUniLocProjMat, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}


/**
 * Render the scene, given the current frame-index
 * @param frameIndex the frame-index
 */
void RenderEngine::render(int frameIndex) {
    // calculate camera matrix
    glm::mat4 viewMat = mEditorCamera->getViewMatrix();
    glUniformMatrix4fv(mUniLocViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

    // render objects
    for(StepAheadAnimationChannel *saaChannel : mStepAheadAnimationChannels) {
        saaChannel->render(frameIndex, mUniLocTransMat);
    }
}


Channel *RenderEngine::pick(int frameIndex, double mouseX, double mouseY, GLFWwindow *window) {
    // reset render
    glDisable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // calculate camera matrix
    glm::mat4 viewMat = mEditorCamera->getViewMatrix();
    glUniformMatrix4fv(mUniLocViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

    // render objects
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    for(int id = 1; id < mStepAheadAnimationChannels.size()+1; ++id) {
        GLint realId = id;
        glUniform1i(mUniLocObjId, realId);
        mStepAheadAnimationChannels[id-1]->render(frameIndex, mUniLocTransMat);
    }

//    glFlush();
//    glFinish();
    unsigned char data[4];
    glReadBuffer(GL_BACK);
    glReadPixels(floor(mouseX), mWindowHeight-floor(mouseY),1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    GLint standardId = 0;
    glUniform1i(mUniLocObjId, standardId);

    int id = (int)data[0] + (int)data[1] * 256 + (int)data[2] * 256 * 256;

    glEnable(GL_MULTISAMPLE);

    if(id == 0)
        return nullptr;

    return mStepAheadAnimationChannels[id-1];
//    glfwSwapBuffers(window);
}


void RenderEngine::addSaaChannel(StepAheadAnimationChannel *saaChannel) {
    mStepAheadAnimationChannels.push_back(saaChannel);
}


Camera &RenderEngine::getEditorCamera() {
    return *mEditorCamera;
}

void RenderEngine::onWindowSizeChange(uint width, uint height) {
    mWindowWidth = width;
    mWindowHeight = height;

    mProjectionMatrix = glm::perspective(
            glm::radians(45.0f),
            ((float)mWindowWidth) / ((float)mWindowHeight),
            CAMERA_NEAR_CLIPPING,
            CAMERA_FAR_CLIPPING
    );
    glUniformMatrix4fv(mUniLocProjMat, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}