//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_STEPAHEADANIMATIONCHANNEL_H
#define PROJECT_STEPAHEADANIMATIONCHANNEL_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Object;
class Path;

class StepAheadAnimationChannel {
public:
    void render(int frameIndex, GLint uniformLocTransMat);
    void addObject(Object* object);
private:
    std::vector<Object*> mObjects;
    Path* mPath = nullptr;
};


#endif //PROJECT_STEPAHEADANIMATIONCHANNEL_H
