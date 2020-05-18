//
// Created by stef on 18.05.20.
//

#ifndef PROJECT_RENDERENGINEWINDOW_H
#define PROJECT_RENDERENGINEWINDOW_H

class Scene;

class RenderEngineWindow {
public:
    RenderEngineWindow(Scene &scene);
    void render();
private:
    Scene &mScene;
};


#endif //PROJECT_RENDERENGINEWINDOW_H
