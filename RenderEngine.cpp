//
// Created by stef on 06.04.20.
//

#include <iostream>
#include <vector>
#include "RenderEngine.h"
#include "Camera.h"
#include "StepAheadAnimationChannel.h"
#include "InputHandler.h"
#include "old_code/Object_DEPRECATED.h"
#include "Orientation.h"
#include "Path.h"
#include "Scene.h"
#include "CSkeleton.h"

//char VERTEX_SHADER_FILENAME[] = "shaders/new_shader.vert";
//char FRAGMENT_SHADER_FILENAME[] = "shaders/new_shader.frag";
//char PICKING_VERTEX_SHADER_FILENAME[] = "shaders/color_picking_shader.vert";
//char PICKING_FRAGMENT_SHADER_FILENAME[] = "shaders/color_picking_shader.frag";


RenderEngine::RenderEngine() : mTransformStack(this) {
    // load standard shaders
//    GLuint vs = InputHandler::loadAndCompileShader(VERTEX_SHADER_FILENAME, GL_VERTEX_SHADER);
//    GLuint fs = InputHandler::loadAndCompileShader(FRAGMENT_SHADER_FILENAME, GL_FRAGMENT_SHADER);
//    mStandardShaderProgram = glCreateProgram();
//    glAttachShader(mStandardShaderProgram, fs);
//    glAttachShader(mStandardShaderProgram, vs);
//    glLinkProgram(mStandardShaderProgram);
//    glUseProgram(mStandardShaderProgram);
//    mUniLocProjMat = mStandardShader.getUniLoc("projectionMatrix");
//    mUniLocTransMat = mStandardShader.getUniLoc("modelMatrix");
//    mUniLocViewMat = mStandardShader.getUniLoc("viewMatrix");
//    mUniLocObjId = mStandardShader.getUniLoc("id");
//    mUniLocTexture = mStandardShader.getUniLoc("texture_diffuse1");
    mStandardShader.setId(0);
//    GLint standardId = 0;
//    glUniform1i(mUniLocObjId, standardId);
    // create new camera
    mEditorCamera = new Camera();
    // generate and load projection matrix
    mProjectionMatrix = glm::perspective(
            glm::radians(CAMERA_FOV),
            ((float)mWindowWidth) / ((float)mWindowHeight),
            CAMERA_NEAR_CLIPPING,
            CAMERA_FAR_CLIPPING
    );
    mStandardShader.setMatrix(PROJECTION_MATRIX, mProjectionMatrix);
//    glUniformMatrix4fv(mUniLocProjMat, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}


void RenderEngine::render(Scene &scene, Picked picked) {
    // calculate & set camera matrix
    glm::mat4 viewMat = mEditorCamera->getViewMatrix();
    mStandardShader.setMatrix(VIEW_MATRIX, viewMat);
    // current variables
    int frameIndex = scene.getClock()->getFrameIndex();
    // render step-ahead animation channels
    std::vector<StepAheadAnimationChannel*> saaChannels = scene.getSaaChannels();
    for(int i = 0; i < saaChannels.size(); ++i) {
        renderSaaChannel(frameIndex, *saaChannels[i], picked);
    }
    std::vector<CSkeleton*> &skeletons = scene.getSkeletons();
    for(auto skeleton : skeletons) {
        skeleton->setTime(frameIndex);
        skeleton->render(&mStandardShader, picked);
    }
}

Picked RenderEngine::pick(Scene &scene, double mouseX, double mouseY, GLFWwindow *window) {
    // prepare render variables & settings for picking
    glDisable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // calculate & set camera matrix
    glm::mat4 viewMat = mEditorCamera->getViewMatrix();
    mStandardShader.setMatrix(VIEW_MATRIX, viewMat);
    // get variables
    int frameIndex = scene.getClock()->getFrameIndex();
    // render objects based on id
    // render saaChannels
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    std::vector<StepAheadAnimationChannel*> &saaChannels = scene.getSaaChannels();
    int obj_id = 1;
    for(auto *saaChannel : saaChannels) {
        mStandardShader.setId(obj_id);
        renderSaaChannel(frameIndex, *saaChannel, {});
        ++obj_id;
    }
    std::vector<CSkeleton*> skeletons = scene.getSkeletons();
    for(auto *skeleton : skeletons) {
        mStandardShader.setId(obj_id);
        skeleton->render(&mStandardShader, Picked::nothing());
        ++obj_id;
    }
    // TODO render skeletons
    // read picked data and calc id
    int id = derivePickedId(mouseX, mouseY);
    // reset render options and variables
    mStandardShader.setId(0);
    glEnable(GL_MULTISAMPLE);
    if(id == 0) {
        // nothing picked
        return {};
    }
    // TODO check which type of channel was picked
    if(id <= saaChannels.size()) {
        StepAheadAnimationChannel *pickedChannel = saaChannels[id - 1];
        FFD *ffd = pickedChannel->getFFD(frameIndex);
        if(ffd == nullptr) {
            return Picked::makeStepAheadChannel(pickedChannel);
        }
        // prepare render variables & settings for picking
        glDisable(GL_MULTISAMPLE);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // render control points
        renderForPicking(pickedChannel, scene);
        //read picked data and derive id
        int id_2 = derivePickedId(mouseX, mouseY);
        // reset render variables and settings
        mStandardShader.setId(0);
        glEnable(GL_MULTISAMPLE);
        // return picked control point index if picked one
        if(id_2 == 0) {
            return Picked::makeStepAheadChannel(pickedChannel);
        }
        return Picked::makeStepAheadChannel(pickedChannel, ffd, id_2-1);
    }
    else {
        // Picked skeleton
        CSkeleton *pickedSkeleton = skeletons[id-saaChannels.size() - 1];
        // prepare render variables & settings for picking
        glDisable(GL_MULTISAMPLE);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // render joints for picking
        pickedSkeleton->renderForPicking(&mStandardShader);
        //read picked data and derive id
        int id_2 = derivePickedId(mouseX, mouseY);
        // reset render variables and settings
        mStandardShader.setId(0);
        glEnable(GL_MULTISAMPLE);
        // return picked control point index if picked one
        if(id_2 == 0) {
            return Picked::makeSkeleton(pickedSkeleton);
        }
        CJoint *pickedJoint = pickedSkeleton->getJoint(id_2-1);
        return Picked::makeSkeleton(pickedSkeleton, pickedJoint);
    }
}

void RenderEngine::renderForPicking(StepAheadAnimationChannel *saaChannel, Scene &scene) {
    int frameIndex = scene.getClock()->getFrameIndex();
    FFD *ffd = saaChannel->getFFD(frameIndex);
    glm::mat4 transformationMatrix = saaChannel->getTransMat();
    GLint uniLocTransMat = mStandardShader.getUniLoc("modelMatrix");
    GLint uniLocTexture = mStandardShader.getUniLocTexture();
    GLint uniLocObjId = mStandardShader.getUniLoc("id");
    ffd->pickControlPoints(transformationMatrix, uniLocTransMat, uniLocTexture, uniLocObjId, *mEditorCamera);
}


void RenderEngine::addSaaChannel(StepAheadAnimationChannel *saaChannel) {
    mStepAheadAnimationChannels_DEPRECATED.push_back(saaChannel);
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
    mStandardShader.setMatrix(PROJECTION_MATRIX, mProjectionMatrix);
//    glUniformMatrix4fv(mUniLocProjMat, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}


void RenderEngine::renderSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel, Picked picked) {
//    Path *path = saaChannel.getPath();
    Model *model = saaChannel.getModel();
    FFD *ffd = saaChannel.getFFD(frameIndex);
    if(model == nullptr) {
        return;
    }
    // determine transformation matrix
//    glm::mat4 transformationMatrix(1.0f);
//    if(path != nullptr) {
//        Orientation orientation = path->orientation(frameIndex);
//        glm::mat4 rotMat = glm::toMat4(orientation.rotation);
//        glm::mat4 transMat = glm::translate(glm::mat4(1.0f), orientation.position);
//        transformationMatrix = glm::scale(transMat*rotMat, orientation.scale);
//    }
//    glm::mat4 transformationMatrix = calcTransMatOfSaaChannel(frameIndex, saaChannel);
    saaChannel.prepare(frameIndex);
    glm::mat4 transformationMatrix = saaChannel.getTransMat();
    mStandardShader.setMatrix(TRANSFORMATION_MATRIX, transformationMatrix);
//    glUniformMatrix4fv(mUniLocTransMat, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    model->Draw(frameIndex, /*mUniLocTexture*/mStandardShader.getUniLocTexture());
    if(ffd != nullptr) {
        int ffdControlPointIndex = -1;
        if(picked.ffd != nullptr) {
            ffdControlPointIndex = picked.controlPointIndex;
        }
        GLint uniLocTransMat = mStandardShader.getUniLoc("modelMatrix");
        GLint uniLocTexture = mStandardShader.getUniLocTexture();
        ffd->renderControlPoints(transformationMatrix, uniLocTransMat, uniLocTexture, *mEditorCamera, ffdControlPointIndex);
    }
}

int RenderEngine::derivePickedId(double mouseX, double mouseY) {
    unsigned char data_2[4];
    glReadBuffer(GL_BACK);
    glReadPixels(floor(mouseX), mWindowHeight-floor(mouseY),1,1, GL_RGBA, GL_UNSIGNED_BYTE, data_2);
    int id_2 = (int)data_2[0] + (int)data_2[1] * 256 + (int)data_2[2] * 256 * 256;
    return id_2;
}

//glm::mat4 RenderEngine::calcTransMatOfSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel) {
//    Path *path = saaChannel.getPath();
//    if(path == nullptr) {
//        return glm::mat4(1.0f);
//    }
//    else {
//        Orientation orientation = path->orientation(frameIndex);
//        glm::mat4 rotMat = glm::toMat4(orientation.rotation);
//        glm::mat4 transMat = glm::translate(glm::mat4(1.0f), orientation.position);
//        glm::mat4 transformationMatrix = glm::scale(transMat*rotMat, orientation.scale);
//        return transformationMatrix;
//    }
//}
