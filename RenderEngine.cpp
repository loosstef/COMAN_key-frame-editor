//
// Created by stef on 06.04.20.
//

#include "RenderEngine.h"
#include "Camera.h"
#include "StepAheadAnimationChannel.h"


RenderEngine::RenderEngine(GLint uniformLocProjMat, GLint uniformLocViewMat, GLint uniformLocTransMat) :
    mUniformLocTransMat(uniformLocTransMat),
    mUniformLocProjMat(uniformLocProjMat),
    mUniformLocViewMat(uniformLocViewMat)
{
    // create new camera
    mEditorCamera = new Camera();
    // generate and load projection matrix
    mProjectionMatrix = glm::perspective(
            glm::radians(45.0f),
            ((float)mWindowWidth) / ((float)mWindowHeight),
            CAMERA_NEAR_CLIPPING,
            CAMERA_FAR_CLIPPING
    );
    glUniformMatrix4fv(mUniformLocProjMat, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}


/**
 * Render the scene, given the current frame-index
 * @param frameIndex the frame-index
 */
void RenderEngine::render(int frameIndex) {
    // render camera
    glm::mat4 viewMat = mEditorCamera->getViewMatrix();
    glUniformMatrix4fv(mUniformLocViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

    // render objects
    for(StepAheadAnimationChannel *saaChannel : mStepAheadAnimationChannels) {
        saaChannel->render(frameIndex, mUniformLocTransMat);
    }
}


void RenderEngine::addSaaChannel(StepAheadAnimationChannel *saaChannel) {
    mStepAheadAnimationChannels.push_back(saaChannel);
}


Camera &RenderEngine::getEditorCamera() {
    return *mEditorCamera;
}
