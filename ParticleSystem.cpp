//
// Created by stef on 09.05.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ParticleSystem.h"
#include "Scene.h"
#include "Particle.h"

ParticleSystem::ParticleSystem(Scene &scene, Model &model)
   : mModel(model)
{
    mGenTill = 0;
}

void ParticleSystem::draw(Scene &scene) {
    // generate more frames if not generated yet
    int currFrameIndex = scene.clock()->getFrameIndex();
    while(currFrameIndex > mGenTill) {
        generate(mGenTill+1, mGenTill+100);
        mGenTill += 100;
    }
    // draw every particle
    for(auto *particle : mParticles) {
        glm::mat4 transMat(1.0f);
        transMat = glm::scale(transMat, glm::vec3(0.1f));
        particle->draw(scene.clock()->getFrameIndex(), mModel, scene);
    }
}
