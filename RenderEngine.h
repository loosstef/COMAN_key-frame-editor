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
class Object;
class Channel;
class GLFWwindow;

class RenderEngine {
public:
    RenderEngine();
    void render(int frameIndex);
    Channel* pick(int frameIndex, double mouseX, double mouseY, GLFWwindow *window);
    void addSaaChannel(StepAheadAnimationChannel *saaChannel);
    Camera& getEditorCamera();
    void onWindowSizeChange(uint width, uint height);
private:
    GLuint mStandardShaderProgram;
    GLint mUniLocTransMat;
    GLint mUniLocViewMat;
    GLint mUniLocProjMat;
    GLint mUniLocObjId;

    uint mWindowWidth = 1940;
    uint mWindowHeight = 1080;
    glm::mat4 mProjectionMatrix;
    Camera* mEditorCamera;
    Camera* mVirtualCamera;
    std::vector<StepAheadAnimationChannel*> mStepAheadAnimationChannels;
};


#endif //PROJECT_RENDERENGINE_H
