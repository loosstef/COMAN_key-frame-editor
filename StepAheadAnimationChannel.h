//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_STEPAHEADANIMATIONCHANNEL_H
#define PROJECT_STEPAHEADANIMATIONCHANNEL_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Channel.h"

class Object_DEPRECATED;
class Path;

class StepAheadAnimationChannel : public Channel {
public:
    ChannelType getType() override { return SAA; }
    void setPath(Path* path);
    Path* getPath() { return mPath; }
    Object_DEPRECATED* getObject() { return mObject; }
    // deprecated functions
    void addObject_DEPRECATED(Object_DEPRECATED* object);
private:
    Object_DEPRECATED *mObject;
//    std::vector<Object*> mObjects;
    Path* mPath = nullptr;
};


#endif //PROJECT_STEPAHEADANIMATIONCHANNEL_H
