//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_RENDERENGINE_H
#define PROJECT_RENDERENGINE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

const float CAMERA_FOV = 45.0f;
const float CAMERA_NEAR_CLIPPING = 1.0f;
const float CAMERA_FAR_CLIPPING = 50.0f;

class Camera;
class StepAheadAnimationChannel;

class RenderEngine {
public:
    RenderEngine(GLint uniformLocProjMat, GLint uniformLocViewMat, GLint uniformLocTransMat);
    void render(int frameIndex);
    void addSaaChannel(StepAheadAnimationChannel *saaChannel);
    Camera& getEditorCamera();
    void onWindowSizeChange(uint width, uint height);
private:
    GLint mUniformLocTransMat;
    GLint mUniformLocViewMat;
    GLint mUniformLocProjMat;
    uint mWindowWidth = 1080;
    uint mWindowHeight = 720;
    glm::mat4 mProjectionMatrix;
    Camera* mEditorCamera;
    Camera* mVirtualCamera;
    std::vector<StepAheadAnimationChannel*> mStepAheadAnimationChannels;
};


#endif //PROJECT_RENDERENGINE_H
