//
// Created by stef on 06.04.20.
//

#include <iostream>
#include "RenderEngine.h"
#include "Camera.h"
#include "StepAheadAnimationChannel.h"
#include "InputHandler.h"
#include "old_code/Object_DEPRECATED.h"
#include "Orientation.h"
#include "Path.h"

char BASIC_VERTEX_SHADER_FILENAME[] = "shaders/new_shader.vert";
char BASIC_FRAGMENT_SHADER_FILENAME[] = "shaders/new_shader.frag";
//char PICKING_VERTEX_SHADER_FILENAME[] = "shaders/color_picking_shader.vert";
//char PICKING_FRAGMENT_SHADER_FILENAME[] = "shaders/color_picking_shader.frag";


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
    mUniLocTexture = glGetUniformLocation(mStandardShaderProgram, "texture_diffuse1"); //material.
    GLint standardId = 0;
    glUniform1i(mUniLocObjId, standardId);

    // create new camera
    mEditorCamera = new Camera();
    // generate and load projection matrix
    mProjectionMatrix = glm::perspective(
            glm::radians(CAMERA_FOV),
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
//    for(StepAheadAnimationChannel *saaChannel : mStepAheadAnimationChannels) {
//        renderSaaChannel(frameIndex, *saaChannel);
//    }

    for(int i = 0; i < mStepAheadAnimationChannels.size(); ++i) {
        renderSaaChannel(frameIndex, *mStepAheadAnimationChannels[i]);
    }

    // TESTING CODE
    // render loaded file
//    GLint standardId = 150;
//    glUniform1i(mUniLocObjId, standardId);
//    glm::mat4 modelMat(1.0f);
//    glUniformMatrix4fv(mUniLocTransMat, 1, GL_FALSE, glm::value_ptr(modelMat));
//    GLint uniTexture = glGetUniformLocation(mStandardShaderProgram, "material.texture_diffuse1");
//    mTestModel.Draw(uniTexture);
//    standardId = 300;
//    glUniform1i(mUniLocObjId, standardId);
}


Picked RenderEngine::pick( int frameIndex, double mouseX, double mouseY, GLFWwindow *window) {
    // reset render
    glDisable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // calculate camera matrix
    glm::mat4 viewMat = mEditorCamera->getViewMatrix();
    glUniformMatrix4fv(mUniLocViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
    // render objects based on id
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    for(int id = 1; id < mStepAheadAnimationChannels.size()+1; ++id) {
        GLint realId = id;
        glUniform1i(mUniLocObjId, realId);
        renderSaaChannel(frameIndex, *mStepAheadAnimationChannels[id-1]);
    }

    unsigned char data[4];
    glReadBuffer(GL_BACK);
    glReadPixels(floor(mouseX), mWindowHeight-floor(mouseY),1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    GLint standardId = 0;
    glUniform1i(mUniLocObjId, standardId);

    int id = (int)data[0] + (int)data[1] * 256 + (int)data[2] * 256 * 256;

    glEnable(GL_MULTISAMPLE);

    if(id == 0) {
        return {};
    }
    return {mStepAheadAnimationChannels[id-1]};
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


void RenderEngine::renderSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel) {
    Path *path = saaChannel.getPath();
    Model *model = saaChannel.getModel();
    FFD *ffd = saaChannel.getFFD(frameIndex);
    if(model == nullptr) {
        return;
    }
    if(path == nullptr) {
        glUniformMatrix4fv(mUniLocTransMat, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        model->Draw(frameIndex, mUniLocTexture);
        if(ffd != nullptr) {
            ffd->renderControlPoints(glm::mat4(1.0f), mUniLocTransMat, mUniLocTexture, *mEditorCamera);
        }
    }
    else {
        Orientation orientation = path->orientation(frameIndex);
        glm::mat4 rotMat = glm::toMat4(orientation.rotation);
        glm::mat4 transMat = glm::translate(glm::mat4(1.0f), orientation.position);
        glm::mat4 transformationMatrix = glm::scale(transMat*rotMat, orientation.scale);
        glUniformMatrix4fv(mUniLocTransMat, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
        model->Draw(frameIndex, mUniLocTexture);
        if(ffd != nullptr) {
            ffd->renderControlPoints(transformationMatrix, mUniLocTransMat, mUniLocTexture, *mEditorCamera);
        }
    }
}
