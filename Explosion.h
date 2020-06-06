//
// Created by stef on 09.05.20.
//

#ifndef PROJECT_EXPLOSION_H
#define PROJECT_EXPLOSION_H

#include "ParticleSystem.h"
#include "vendor/nlohmann/json.hpp"

class Scene;
class Model;

class Explosion : public ParticleSystem {
public:
    Explosion(Model &model, int when, int particlesCount = 1000);
    explicit Explosion(nlohmann::json &j);
    [[nodiscard]] int getFrameOfExplosion() const { return mFrameOfExplosion; }
    [[nodiscard]] int particlesCount() const { return PARTICLES_COUNT; }
private:
    // functions
    void generate(int firstIndex, int lastIndex) override;
    // variables
    int mFrameOfExplosion;
    // constants
    const int PARTICLES_COUNT;
};


#endif //PROJECT_EXPLOSION_H
