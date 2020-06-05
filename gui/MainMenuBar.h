//
// Created by stef on 21.05.20.
//

#ifndef PROJECT_MAINMENUBAR_H
#define PROJECT_MAINMENUBAR_H

class Scene;
class WindowRenderEngine;

class MainMenuBar {
public:
    MainMenuBar(Scene &scene, WindowRenderEngine &wre);
    void render();
private:
    Scene &mScene;
    WindowRenderEngine &mWRE;
    void showFileMenu();
    void showViewMenu();
    void showLoadFile();
    void showSaveFile();
    void showAddSkyboxPopup();
    void showAddSaaChannelPopup();
    void showAddSkeletonPopup();
    void showAddPlantPopup();
};


#endif //PROJECT_MAINMENUBAR_H
