//
// Created by stef on 21.05.20.
//

#include "MainMenuBar.h"
#include "WindowRenderEngine.h"
#include "../Scene.h"
#include "../vendor/imgui/imgui.h"
#include "../LinearPath.h"
#include "../Model.h"

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
    showLoadFile();
    showSaveFile();
    showAddSkyboxPopup();
    showAddSaaChannelPopup();
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
        if (ImGui::Button("Save")) {
            saaChannel->name = channelName;
            saaChannel->setObject(new Model(path));
            mScene.add(saaChannel);
            saaChannel->setPath(new LinearPath());
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