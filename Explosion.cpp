//
// Created by stef on 09.05.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Explosion.h"
#include "Particle.h"

Explosion::Explosion(Scene &scene, Model &model, int when) : ParticleSystem(scene, model) {
    mFrameOfExplosion = when;
}

void Explosion::generate(int firstIndex, int lastIndex) {
    if(firstIndex <= mFrameOfExplosion && mFrameOfExplosion <= lastIndex) {
        glm::mat4 transMat(1.0f);
        transMat = glm::scale(transMat, glm::vec3(0.1f));
        for(int i = 0; i < PARTICLES_COUNT; ++i) {
            float random_x = (2.0f*((float)rand() / (float) RAND_MAX)) - 1.0f;
            float random_y = (2.0f*((float)rand() / (float) RAND_MAX)) - 1.0f;
            float random_z = (2.0f*((float)rand() / (float) RAND_MAX)) - 1.0f;
            glm::vec3 moveVec(random_x, random_y, random_z);
            auto *particle = new Particle(transMat, mFrameOfExplosion, mFrameOfExplosion+200, moveVec/10.0f);
            mParticles.push_back(particle);
        }
    }
}
