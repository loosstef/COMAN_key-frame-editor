//
// Created by stef on 09.05.20.
//

#ifndef PROJECT_PARTICLESYSTEM_H
#define PROJECT_PARTICLESYSTEM_H

#include <vector>
#include "Model.h"

class Scene;
class Particle;

class ParticleSystem {
public:
    ParticleSystem(Model &model);
    void draw(Scene &scene);
protected:
    std::vector<Particle*> mParticles;
private:
    virtual void generate(int firstIndex, int lastIndex) = 0;
    int mGenTill;    // keeps track of till what moment the particles were generated
    Model &mModel;
};


#endif //PROJECT_PARTICLESYSTEM_H
