//
// Created by stef on 06.04.20.
//

#ifndef PROJECT_STEPAHEADANIMATIONCHANNEL_H
#define PROJECT_STEPAHEADANIMATIONCHANNEL_H

#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Channel.h"
#include "vendor/nlohmann/json.hpp"
#include "LinearPath.h"

class Path;
class Model;
class FFD;

class StepAheadAnimationChannel : public Channel {
public:
    StepAheadAnimationChannel() : mTransMat(1.0f) {}
    explicit StepAheadAnimationChannel(nlohmann::json j);
    ChannelType getType() override { return SAA; }
    void setPath(LinearPath* path);
    Path* getPath() { return mPath; }
    Model* getModel() { return mModel; }
    void setObject(Model* model);
    void addFFD(int frameIndex, FFD *ffd);
    FFD* getFFD(int frameIndex);
    void removeFFD(int frameIndex);
    std::vector<int>& getFFDIndices() { return mFFFDFrameIndices; }
    void setTransMat(glm::mat4 &mat);
    glm::mat4 getTransMat();
    void prepare(int frameIndex);
    void tellModelFFDChanged(FFD *ffd, int frameIndex);
    nlohmann::json to_json();
    std::string name;
private:
    Model *mModel;
    LinearPath* mPath = nullptr;
    std::vector<FFD*> mFFDs;
    std::vector<int> mFFFDFrameIndices;
    glm::mat4 mTransMat;
};


#endif //PROJECT_STEPAHEADANIMATIONCHANNEL_H
