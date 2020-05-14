//
// Created by stef on 09.05.20.
//

#ifndef PROJECT_EXPLOSION_H
#define PROJECT_EXPLOSION_H

#include "ParticleSystem.h"

class Scene;
class Model;

class Explosion : public ParticleSystem {
public:
    Explosion(Scene &scene, Model &model, int when);
private:
    // functions
    void generate(int firstIndex, int lastIndex) override;
    // variables
    int mFrameOfExplosion;
    // constants
    const int PARTICLES_COUNT = 1000;
};


#endif //PROJECT_EXPLOSION_H
