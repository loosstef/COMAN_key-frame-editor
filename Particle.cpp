//
// Created by stef on 09.05.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Particle.h"
#include "Scene.h"
#include "Model.h"

Particle::Particle(glm::mat4 baseTransMat, int firstFrame, int lastFrame, glm::vec3 moveVec) {
    // set local variables
    mBaseTransMat = baseTransMat;
    mFirstFrameIndex = firstFrame;
    mLastFrameIndex = lastFrame;
    mMoveVec = moveVec;
}

void Particle::draw(int frameIndex, Model &model, Scene &scene) {
    // check if particle should be drawn
    if(frameIndex < mFirstFrameIndex || frameIndex > mLastFrameIndex) {
        return;
    }
    glm::mat4 currTransMat = glm::translate(glm::mat4(1.0f), mMoveVec*(float)(frameIndex-mFirstFrameIndex)) * mBaseTransMat;
    // TODO: update to use stack
    scene.getRenderEngine().getStandardShader()->setMatrix(TRANSFORMATION_MATRIX, currTransMat);
    model.Draw(frameIndex, scene.getRenderEngine().getStandardShader()->getUniLocTexture());
}
