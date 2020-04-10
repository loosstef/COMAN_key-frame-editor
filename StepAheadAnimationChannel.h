//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_STEPAHEADANIMATIONCHANNEL_H
#define PROJECT_STEPAHEADANIMATIONCHANNEL_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Channel.h"

class Object;
class Path;

class StepAheadAnimationChannel : public Channel {
public:
    ChannelType getType() override { return SAA; }
    void render(int frameIndex, GLint uniformLocTransMat);
    void addObject(Object* object);
    void setPath(Path* path);
    Path* getPath() { return mPath; }
    Object* getObject(int index = 0);
private:
    std::vector<Object*> mObjects;
    Path* mPath = nullptr;
};


#endif //PROJECT_STEPAHEADANIMATIONCHANNEL_H
