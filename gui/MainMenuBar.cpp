//
// Created by stef on 21.05.20.
//

#include <sstream>
#include "MainMenuBar.h"
#include "WindowRenderEngine.h"
#include "../Scene.h"
#include "../vendor/imgui/imgui.h"
#include "../LinearPath.h"
#include "../Model.h"
#include "../CSkeleton.h"
#include "../LSystem.h"
#include "../Plant.h"

MainMenuBar::MainMenuBar(Scene &scene, WindowRenderEngine &wre) : mScene(scene), mWRE(wre) {
}

void MainMenuBar::render() {
    showFileMenu();
    showViewMenu();
}


void MainMenuBar::showFileMenu() {
    bool shouldOpenLoadScenePopup = false;
    bool shouldOpenSaveScenePopup = false;
    bool shouldOpenSkyboxPopup = false;
    bool shouldOpenSaaChannelPopup = false;
    bool shouldOpenSkeletonPopup = false;
    bool shouldOpenPlantPopup = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("new scene")) {
                mScene.reset();
            }
            if (ImGui::MenuItem("load scene")) {
                shouldOpenLoadScenePopup = true;
            }
            if (ImGui::MenuItem("save scene")) {
                shouldOpenSaveScenePopup = true;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("skybox")) {
                shouldOpenSkyboxPopup = true;
            }
            if(ImGui::MenuItem("step ahead animation")) {
                shouldOpenSaaChannelPopup = true;
            }
            if(ImGui::MenuItem("skeleton")) {
                shouldOpenSkeletonPopup = true;
            }
            if(ImGui::MenuItem("plant")) {
                shouldOpenPlantPopup = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if(shouldOpenLoadScenePopup && !ImGui::IsPopupOpen("load scene from file")) {
        ImGui::OpenPopup("load scene from file");
        shouldOpenLoadScenePopup = false;
    }
    if(shouldOpenSaveScenePopup && !ImGui::IsPopupOpen("save scene")) {
        ImGui::OpenPopup("save scene");
        shouldOpenSaveScenePopup = false;
    }
    if(shouldOpenSkyboxPopup && !ImGui::IsPopupOpen("new skybox")) {
        ImGui::OpenPopup("new skybox");
        shouldOpenSkyboxPopup = false;
    }
    if(shouldOpenSaaChannelPopup && !ImGui::IsPopupOpen("add step ahead animation")) {
        ImGui::OpenPopup("add step ahead animation");
        shouldOpenSaaChannelPopup = false;
    }
    if(shouldOpenSkeletonPopup && !ImGui::IsPopupOpen("add skeleton")) {
        ImGui::OpenPopup("add skeleton");
        shouldOpenSkeletonPopup = false;
    }
    if(shouldOpenPlantPopup && !ImGui::IsPopupOpen("add plant")) {
        ImGui::OpenPopup("add plant");
        shouldOpenPlantPopup = false;
    }
    showLoadFile();
    showSaveFile();
    showAddSkyboxPopup();
    showAddSaaChannelPopup();
    showAddSkeletonPopup();
    showAddPlantPopup();
}


void MainMenuBar::showLoadFile() {
    const int PATH_BUFFER_SIZE = 512;
    static char path[PATH_BUFFER_SIZE] = "save.json";
    if (ImGui::BeginPopupModal("load scene from file", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("default", path, PATH_BUFFER_SIZE);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // load btn
        if (ImGui::Button("Load")) {
            mScene.load(path);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void MainMenuBar::showSaveFile() {
    const int PATH_BUFFER_SIZE = 512;
    static char path[PATH_BUFFER_SIZE] = "save.json";
    if (ImGui::BeginPopupModal("save scene", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("path", path, PATH_BUFFER_SIZE);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // load btn
        if (ImGui::Button("Save")) {
            mScene.save(path);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void MainMenuBar::showAddSkyboxPopup() {
    const int PATH_BUFFER_SIZE = 512;
    static std::vector<std::string> paths {
        "models/skybox/right.jpg",
        "models/skybox/left.jpg",
        "models/skybox/top.jpg",
        "models/skybox/bottom.jpg",
        "models/skybox/front.jpg",
        "models/skybox/back.jpg"
    };
    for(auto &path : paths) {
        path.resize(PATH_BUFFER_SIZE);
    }
    if (ImGui::BeginPopupModal("new skybox", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("right", paths[0].data(), PATH_BUFFER_SIZE);
        ImGui::InputText("left", paths[1].data(), PATH_BUFFER_SIZE);
        ImGui::InputText("top", paths[2].data(), PATH_BUFFER_SIZE);
        ImGui::InputText("bottom", paths[3].data(), PATH_BUFFER_SIZE);
        ImGui::InputText("front", paths[4].data(), PATH_BUFFER_SIZE);
        ImGui::InputText("back", paths[5].data(), PATH_BUFFER_SIZE);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // load btn
        if (ImGui::Button("Add")) {
            mScene.setSkyBox(paths);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void MainMenuBar::showAddSaaChannelPopup() {
    StepAheadAnimationChannel *saaChannel = new StepAheadAnimationChannel();
    const int PATH_BUFFER_SIZE = 512;
    static char channelName[PATH_BUFFER_SIZE] = "Step ahead animation";
    static char path[PATH_BUFFER_SIZE] = "models/spongebob.obj";
    if (ImGui::BeginPopupModal("add step ahead animation", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("name", channelName, PATH_BUFFER_SIZE);
        ImGui::InputText("path", path, PATH_BUFFER_SIZE);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            delete saaChannel;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // load btn
        if (ImGui::Button("Create")) {
            saaChannel->name = channelName;
            saaChannel->setObject(new Model(path));
            mScene.add(saaChannel);
            saaChannel->setPath(new LinearPath());
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void MainMenuBar::showAddSkeletonPopup() {
    const int PATH_BUFFER_SIZE = 512;
//    static char channelName[PATH_BUFFER_SIZE] = "skeleton";
    static char path[PATH_BUFFER_SIZE] = "models/skeleton.skl";
    if (ImGui::BeginPopupModal("add skeleton", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
//        ImGui::InputText("name", channelName, PATH_BUFFER_SIZE);
        ImGui::InputText("path", path, PATH_BUFFER_SIZE);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // load btn
        if (ImGui::Button("Load")) {
            CSkeleton *skeleton = new CSkeleton(path);
            mScene.add(skeleton);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void MainMenuBar::showAddPlantPopup() {
    const int RULES_BUFFER_SIZE = 4096;
    static char rules[RULES_BUFFER_SIZE]  = "F->F[+F]F[-RF]F:1.0";
    static int treeDepth = 3;
    static char startString[256] = "F";
    if (ImGui::BeginPopupModal("add plant", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputInt("depth", &treeDepth);
        ImGui::InputTextMultiline("rules", rules, RULES_BUFFER_SIZE);
        ImGui::InputText("starting situation", startString, 256);
        // cancel btn
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        // load btn
        if (ImGui::Button("Create")) {
            LSystem lSystem(treeDepth);
            std::istringstream stream_rules(rules);
            std::string str_rule;
            while(std::getline(stream_rules, str_rule, ';')) {
                lSystem.addRule(str_rule);
            }
            Plant *plant = new Plant(lSystem.produce(startString));
            mScene.add(plant);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}


void MainMenuBar::showViewMenu() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Timeline", "", mWRE.showTimeLineWindow)) {
                mWRE.showTimeLineWindow = !mWRE.showTimeLineWindow;
            }
            if(ImGui::MenuItem("Render Engine", "", mWRE.showRenderEngineWindow)) {
                mWRE.showRenderEngineWindow = !mWRE.showRenderEngineWindow;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
