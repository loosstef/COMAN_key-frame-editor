//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_RENDERENGINE_H
#define PROJECT_RENDERENGINE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Picked.cpp"
#include "StandardShader.h"

const float CAMERA_FOV = 45.0f;
const float CAMERA_NEAR_CLIPPING = 1.0f;
const float CAMERA_FAR_CLIPPING = 50.0f;

class Camera;
class StepAheadAnimationChannel;
class Object_DEPRECATED;
class Channel;
class GLFWwindow;

class RenderEngine {
public:
    RenderEngine();
    void render(int frameIndex, Picked picked);
    Picked pick(int frameIndex, double mouseX, double mouseY, GLFWwindow *window);
    void addSaaChannel(StepAheadAnimationChannel *saaChannel);
    Camera& getEditorCamera();
    void onWindowSizeChange(uint width, uint height);
private:
    void renderSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel, Picked picked);
//    glm::mat4 calcTransMatOfSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel);
    StandardShader mStandardShader;
//    GLint mUniLocTransMat;
//    GLint mUniLocViewMat;
//    GLint mUniLocProjMat;
//    GLint mUniLocObjId;
//    GLint mUniLocTexture;

    uint mWindowWidth = 1940;
    uint mWindowHeight = 1080;
    glm::mat4 mProjectionMatrix;
    Camera* mEditorCamera;
    Camera* mVirtualCamera;
    std::vector<StepAheadAnimationChannel*> mStepAheadAnimationChannels;

    // debug variable
//    Model mTestModel;
};


#endif //PROJECT_RENDERENGINE_H
