//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_STEPAHEADANIMATIONCHANNEL_H
#define PROJECT_STEPAHEADANIMATIONCHANNEL_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Channel.h"
#include "Model.h"

class Object_DEPRECATED;
class Path;

class StepAheadAnimationChannel : public Channel {
public:
    ChannelType getType() override { return SAA; }
    void setPath(Path* path);
    Path* getPath() { return mPath; }
    Model* getModel() { return mModel; }
    void setObject(Model* model);
private:
    Model *mModel;
    Path* mPath = nullptr;
};


#endif //PROJECT_STEPAHEADANIMATIONCHANNEL_H
