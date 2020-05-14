//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_RENDERENGINE_H
#define PROJECT_RENDERENGINE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Picked.h"
#include "StandardShader.h"
#include "TransformStack.h"

const float CAMERA_FOV = 45.0f;
const float CAMERA_NEAR_CLIPPING = 0.1f;
const float CAMERA_FAR_CLIPPING = 50.0f;

class Camera;
class StepAheadAnimationChannel;
class Object_DEPRECATED;
class Channel;
class GLFWwindow;
class Scene;

class RenderEngine {
public:
    RenderEngine();
    void render(Scene &scene, Picked picked);
    Picked pick(Scene &scene, double mouseX, double mouseY, GLFWwindow *window);
    void addSaaChannel(StepAheadAnimationChannel *saaChannel);
    Camera& getEditorCamera();
    void onWindowSizeChange(uint width, uint height);
    uint getWindowHeight() { return mWindowHeight; }
    uint getWindowWidth() { return mWindowWidth; }
    glm::mat4 getProjectionMatrix() { return mProjectionMatrix; }
    StandardShader *getStandardShader() { return &mStandardShader; }
    Shader* getShader() { return mCurrShader; }
    TransformStack& transformStack() { return mTransformStack; }
    void useShader(Shader &shader);
private:
    void renderSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel, Picked picked);
    void renderForPicking(StepAheadAnimationChannel *saaChannel, Scene &scene);
    int derivePickedId(double mouseX, double mouseY);
    uint mWindowWidth = 1940;
    uint mWindowHeight = 1080;
    glm::mat4 mProjectionMatrix;
    TransformStack mTransformStack;
    // cameras
    Camera *mCurrCamera;
    Camera* mEditorCamera;
    Camera* mVirtualCamera;
    // shaders
    Shader *mCurrShader;
    StandardShader mStandardShader;
    Shader mSkyBoxShader;
    // deprectated variables
    std::vector<StepAheadAnimationChannel*> mStepAheadAnimationChannels_DEPRECATED;
};


#endif //PROJECT_RENDERENGINE_H
