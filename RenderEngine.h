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

//const float CAMERA_FOV = 45.0f;
//const float CAMERA_NEAR_CLIPPING = 0.1f;
//const float CAMERA_FAR_CLIPPING = 50.0f;

class Camera;
class StepAheadAnimationChannel;
class Channel;
class GLFWwindow;
class Scene;

class RenderEngine {
public:
    // constructor
    RenderEngine(int width = 1940, int height = 1080);
    // render
    void render(Scene &scene, Picked picked);
    Picked pick(Scene &scene, double mouseX, double mouseY, GLFWwindow *window);
    // set camera
    void useCamera(Camera &camera);
    // getters
    Camera& editorCamera();
    Camera& camera();
    Shader* shader();
    uint getWindowHeight() const { return mWindowHeight; }
    uint getWindowWidth() const { return mWindowWidth; }
    TransformStack& transformStack() { return mTransformStack; }
    // events
    void onWindowSizeChange(uint width, uint height);
private:
    // set state
    void useShader(Shader &shader);
    // render
    void renderSaaChannel(int frameIndex, StepAheadAnimationChannel &saaChannel, Picked picked);
    void renderForPicking(StepAheadAnimationChannel *saaChannel, Scene &scene);
    int derivePickedId(double mouseX, double mouseY);
    // member variables
    uint mWindowWidth;
    uint mWindowHeight;
    TransformStack mTransformStack;
    // cameras
    Camera *mCurrCamera;
    Camera *mEditorCamera;
    // shaders
    Shader *mCurrShader;
    StandardShader mStandardShader;
    Shader mSkyBoxShader;
};


#endif //PROJECT_RENDERENGINE_H
