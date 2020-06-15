//
// Created by stef on 21.04.20.
//

#include <fstream>
#include "Scene.h"
#include "SkyBox.h"
#include "Camera.h"
#include "vendor/nlohmann/json.hpp"
#include "StepAheadAnimationChannel.h"
#include "jsonCast.h"
#include "CSkeleton.h"
#include "Explosion.h"

/**
 * Initialize the scene-object
 * @param re the used render engine
 * @param clock the clock of this scene
 */
void Scene::init(RenderEngine *re, Clock *clock) {
    mRenderEngine = re;
    mClock = clock;
}

/**
 * Destructor
 */
Scene::~Scene() {
    delete mRenderEngine;
    delete mClock;
    delete mSkyBox;
}

void Scene::add(StepAheadAnimationChannel *saaChannel) {
    mSaaChannels.push_back(saaChannel);
}

void Scene::add(CSkeleton *skeleton) {
    mSkeletons.push_back(skeleton);
}

void Scene::add(Plant *plant) {
    mPlants.push_back(plant);
}

void Scene::add(Camera *camera) {
    mCameras.push_back(camera);
}

void Scene::add(ParticleSystem *particleSystem) {
    mParticleSystems.push_back(particleSystem);
}

void Scene::setSkyBox(std::vector<std::string> &faces) {
    if(mSkyBox != nullptr) {
        delete mSkyBox;
    }
    mSkyBox = new SkyBox(faces);
}

/**
 * Call this function before rendering the scene.
 * This will update all time-dependant channels based on the
 * current time.
 */
void Scene::update() {
    int currFrame = mClock->getFrameIndex();
    for(auto *camera : mCameras) {
        camera->update(currFrame);
    }
}

/**
 * Save the current scene.
 * @param path path of save-file
 */
void Scene::save(std::string path) {
    nlohmann::json j;
    // save skybox
    if(mSkyBox != nullptr)
        j["skybox"] = mSkyBox->to_json();
    // save step ahead animations
    if(!mSaaChannels.empty()) {
        nlohmann::json j_saaChannels = nlohmann::json::array();
        for(auto &saaChannel : mSaaChannels) {
            j_saaChannels.push_back(saaChannel->to_json());
        }
        j["step_ahead_animation_channels"] = j_saaChannels;
    }
    // save skeleton
    if(!mSkeletons.empty()) {
        j["skeletons"] = nlohmann::json::array();
        for(CSkeleton *skeleton : mSkeletons) {
            nlohmann::json j_skeleton;
            to_json(j_skeleton, *skeleton);
            j["skeletons"].push_back(j_skeleton);
        }
    }
    // save Plant
    if(!mPlants.empty()) {
        j["plants"] = nlohmann::json::array();
        for(Plant *plant : mPlants) {
            j["plants"].push_back(*plant);
        }
    }
    // save particle-system
    if(!mParticleSystems.empty()) {
        j["particle_systems"] = nlohmann::json::array();
        for(ParticleSystem *ps : mParticleSystems) {
            Explosion *explosion = (Explosion*) ps;
            nlohmann::json j_explosion;
            to_json(j_explosion, *explosion);
            j["particle_systems"].push_back(j_explosion);
        }
    }
    std::fstream file(path, std::fstream::out);
    file << j;
    file.close();
}

/**
 * Load a scene from file
 * @param path path of scene-file
 */
void Scene::load(std::string path) {
    // reset all
    reset();
    // open file
    std::ifstream ifs(path);
    nlohmann::json j = nlohmann::json::parse(ifs);
    // load skybox
    if(j.find("skybox") != j.end()) {
        mSkyBox = new SkyBox(j["skybox"].get<nlohmann::json>());
    }
    // load step ahead animation channels
    if(j.find("step_ahead_animation_channels") != j.end()) {
        nlohmann::json j_saaChannels = j["step_ahead_animation_channels"];
        for(int i = 0; i < j_saaChannels.size(); ++i) {
            auto *newSaaChannel = new StepAheadAnimationChannel(j_saaChannels[i]);
            mSaaChannels.push_back(newSaaChannel);
        }
    }
    // load skeletons
    if(j.find("skeletons") != j.end()) {
        for(nlohmann::json &j_skeleton : j["skeletons"]) {
            CSkeleton *newSkeleton = new CSkeleton(j_skeleton);
            mSkeletons.push_back(newSkeleton);
        }
    }
    // load plants
    if(j.find("plants") != j.end()) {
        for(nlohmann::json &j_plant : j["plants"]) {
            Plant *newPlant = new Plant(j_plant);
            mPlants.push_back(newPlant);
        }
    }
    // load particle systems
    if(j.find("particle_systems") != j.end()) {
        for(nlohmann::json &j_ps : j["particle_systems"]) {
            Explosion *explosion = new Explosion(j_ps);
            mParticleSystems.push_back(explosion);
        }
    }
    // close file
    ifs.close();
}

/**
 * reset the current scene. Making it empty.
 */
void Scene::reset() {
    // TODO: correctly free all memory
    delete mSkyBox;
    mSkyBox = nullptr;
    mSaaChannels.clear();
    for(auto *skeleton : mSkeletons)
        delete skeleton;
    mSkeletons.clear();
    for(auto *plant : mPlants)
        delete plant;
    mPlants.clear();
    mCameras.clear();
    for(auto *ps : mParticleSystems)
        delete ps;
    mParticleSystems.clear();
}
