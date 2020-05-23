//
// Created by stef on 06.04.20.
//

#include <iostream>
#include <vector>
#include "assert.h"
#include "RenderEngine.h"
#include "Camera.h"
#include "StepAheadAnimationChannel.h"
#include "InputHandler.h"
#include "old_code/Object_DEPRECATED.h"
#include "Orientation.h"
#include "Path.h"
#include "Scene.h"
#include "CSkeleton.h"
#include "SkyBox.h"
#include "FFD.h"


//char VERTEX_SHADER_FILENAME[] = "shaders/standard.vert";
//char FRAGMENT_SHADER_FILENAME[] = "shaders/standard.frag";
//char PICKING_VERTEX_SHADER_FILENAME[] = "shaders/color_picking_shader.vert";
//char PICKING_FRAGMENT_SHADER_FILENAME[] = "shaders/color_picking_shader.frag";


RenderEngine::RenderEngine() : mTransformStack(this),
    mSkyBoxShader("shaders/skybox.vert", "shaders/skybox.frag", "skybox")
{
    // set standard values of member variables
    mWindowWidth = 1940;
    mWindowHeight = 1080;
    // set id of standard shader to 0
    mStandardShader.setId(0);
    // create new camera
    mEditorCamera = new Camera(mWindowWidth, mWindowHeight, "editor cam");
    mCurrCamera = mEditorCamera;
    // generate and load projection matrix
//    mProjectionMatrix = glm::perspective(
//            glm::radians(CAMERA_FOV),
//            ((float)mWindowWidth) / ((float)mWindowHeight),
//            CAMERA_NEAR_CLIPPING,
//            CAMERA_FAR_CLIPPING
//    );
    glm::mat4 projMat = mCurrCamera->getProjectionMatrix();
    mStandardShader.setMatrix(PROJECTION_MATRIX, projMat);
    useShader(mStandardShader);
}


void RenderEngine::render(Scene &scene, Picked picked) {
    // clear buffers
    useShader(mStandardShader);
    // calculate & set camera matrix
    glm::mat4 viewMat = mCurrCamera->getViewMatrix();
    mStandardShader.setMatrix(VIEW_MATRIX, viewMat);
    // set projection matrix
    glm::mat4 projMat = mCurrCamera->getProjectionMatrix();
    mStandardShader.setMatrix(PROJECTION_MATRIX, projMat);
    // current variables
    int frameIndex = scene.clock()->getFrameIndex();
    // render step-ahead animation channels
    std::vector<StepAheadAnimationChannel*> saaChannels = scene.saaChannels();
    for(int i = 0; i < saaChannels.size(); ++i) {
        renderSaaChannel(frameIndex, *saaChannels[i], picked);
    }
    // render skeletons
    std::vector<CSkeleton*> &skeletons = scene.skeletons();
    for(auto skeleton : skeletons) {
        skeleton->setTime(frameIndex);
        skeleton->render(&mStandardShader, picked);
    }
    // render plants
    std::vector<Plant*> &plants = scene.plants();
    for(auto plant : plants) {
        plant->draw(*this, mStandardShader);
    }
    // render camera
    std::vector<Camera*> &cameras = scene.cameras();
    for(auto camera : cameras) {
        camera->draw(scene);
    }
    // render skybox
    if(scene.skyBox() != nullptr) {
        useShader(mSkyBoxShader);
        scene.skyBox()->draw(scene);
    }

}

Picked RenderEngine::pick(Scene &scene, double mouseX, double mouseY, GLFWwindow *window) {
    // use standard shader
    useShader(mStandardShader);
    // calculate & set camera matrix
    glm::mat4 viewMat = mCurrCamera->getViewMatrix();
    mStandardShader.setMatrix(VIEW_MATRIX, viewMat);
    // set projection matrix
    glm::mat4 projMat = mCurrCamera->getProjectionMatrix();
    mStandardShader.setMatrix(PROJECTION_MATRIX, projMat);
    // prepare render variables & settings for picking
    glDisable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // get variables
    int frameIndex = scene.clock()->getFrameIndex();
    // render objects based on id
    // render saaChannels
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    std::vector<StepAheadAnimationChannel*> &saaChannels = scene.saaChannels();
    int obj_id = 1;
    for(auto *saaChannel : saaChannels) {
        mStandardShader.setId(obj_id);
        renderSaaChannel(frameIndex, *saaChannel, {});
        ++obj_id;
    }
    std::vector<CSkeleton*> skeletons = scene.skeletons();
    for(auto *skeleton : skeletons) {
        mStandardShader.setId(obj_id);
        skeleton->render(&mStandardShader, Picked::nothing());
        ++obj_id;
    }
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
    int frameIndex = scene.clock()->getFrameIndex();
    FFD *ffd = saaChannel->getFFD(frameIndex);
    glm::mat4 transformationMatrix = saaChannel->getTransMat();
    GLint uniLocTransMat = mStandardShader.getUniLoc("modelMatrix");
    GLint uniLocTexture = mStandardShader.getUniLocTexture();
    GLint uniLocObjId = mStandardShader.getUniLoc("id");
    ffd->pickControlPoints(transformationMatrix, uniLocTransMat, uniLocTexture, uniLocObjId, *mEditorCamera);
}


Camera &RenderEngine::editorCamera() {
    return *mEditorCamera;
}

void RenderEngine::onWindowSizeChange(uint width, uint height) {
    mWindowWidth = width;
    mWindowHeight = height;
    mEditorCamera->setWindowSize(width, height);
    // TODO: resize all extra cameras
//    mVirtualCamera->setWindowSize(width, height);
//    mProjectionMatrix = glm::perspective(
//            glm::radians(45.0f),
//            ((float)mWindowWidth) / ((float)mWindowHeight),
//            CAMERA_NEAR_CLIPPING,
//            CAMERA_FAR_CLIPPING
//    );
//    mStandardShader.setMatrix(PROJECTION_MATRIX, mProjectionMatrix);
//    glUniformMatrix4fv(mUniLocProjMat, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}


void RenderEngine::renderSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel, Picked picked) {
    // retrieve model and ffd
    Model *model = saaChannel.getModel();
    FFD *ffd = saaChannel.getFFD(frameIndex);
    // check if saa-channel contains model
    if(model == nullptr) {
        std::cerr << "Error: tried to render step-ahead animation channel but didn't contain a model. Skipped render." << std::endl;
        return;
    }
    // prepare channel based on current frame index
    saaChannel.prepare(frameIndex);
    // retrieve and set transformation matrix
    glm::mat4 transformationMatrix = saaChannel.getTransMat();
    mStandardShader.setMatrix(TRANSFORMATION_MATRIX, transformationMatrix);
    // draw model
    model->draw(frameIndex, mStandardShader.getUniLocTexture());
    // draw ffd if exists
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

void RenderEngine::useShader(Shader &shader) {
    mCurrShader = &shader;
    shader.use();
}

void RenderEngine::useCamera(Camera &camera) {
    mCurrCamera = &camera;
}

Camera &RenderEngine::camera() {
    assert(mCurrCamera != nullptr);
    return *mCurrCamera;
}

Shader *RenderEngine::shader() {
    assert(mCurrShader != nullptr);
    return mCurrShader;
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
