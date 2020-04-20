//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_STEPAHEADANIMATIONCHANNEL_H
#define PROJECT_STEPAHEADANIMATIONCHANNEL_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Channel.h"

class Object_DEPRECATED;
class Path;
class Model;
class FFD;

class StepAheadAnimationChannel : public Channel {
public:
    ChannelType getType() override { return SAA; }
    void setPath(Path* path);
    Path* getPath() { return mPath; }
    Model* getModel() { return mModel; }
    void setObject(Model* model);
    void addFFD(int frameIndex, FFD *ffd);
    FFD* getFFD(int frameIndex);
//    void setFFD(FFD *ffd);
//    FFD* getFFD() { return mFFD; }
    std::string name;
private:
    Model *mModel;
    Path* mPath = nullptr;
    std::vector<FFD*> mFFDs;
    std::vector<int> mFFFDFrameIndices;
//    FFD *mFFD = nullptr;
};


#endif //PROJECT_STEPAHEADANIMATIONCHANNEL_H
