//
// Created by stef on 03.03.20.
//

#ifndef ANTONGERDELAN_MOVER_H
#define ANTONGERDELAN_MOVER_H


#include <chrono>
#include "../Object.h"
#include "Path_old.h"
#include "../Chrono.h"

class Mover_old {
public:
    Mover_old(Object &obj, Path_old &path);
    glm::mat4 translation(float time);
    void draw(GLint uniTrans);
    void start();
    void pause();
private:
    Object &mObject;
    Path_old &mPath;
    Chrono mChrono;
};


#endif //ANTONGERDELAN_MOVER_H
