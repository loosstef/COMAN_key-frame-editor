//
// Created by stef on 03.03.20.
//

#ifndef ANTONGERDELAN_MOVER_H
#define ANTONGERDELAN_MOVER_H


#include <chrono>
#include "Object_DEPRECATED.h"
#include "Path_old.h"
#include "Chrono_old.h"

class Mover_old {
public:
    Mover_old(Object_DEPRECATED &obj, Path_old &path);
    glm::mat4 translation(float time);
    void draw(GLint uniTrans);
    void start();
    void pause();
private:
    Object_DEPRECATED &mObject;
    Path_old &mPath;
    Chrono_old mChrono;
};


#endif //ANTONGERDELAN_MOVER_H
