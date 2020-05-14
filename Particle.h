//
// Created by stef on 09.05.20.
//

#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H


#include <glm/detail/type_mat4x4.hpp>

class Model;
class Scene;

class Particle {
public:
    Particle(glm::mat4 baseTransMat, int firstFrame, int lastFrame, glm::vec3 moveVec);
    void draw(int frameIndex, Model &model, Scene &scene);
private:
    glm::mat4 mBaseTransMat;
    int mFirstFrameIndex;
    int mLastFrameIndex;
    glm::vec3 mMoveVec;

};


#endif //PROJECT_PARTICLE_H
