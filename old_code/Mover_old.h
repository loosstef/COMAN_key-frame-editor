//
// Created by stef on 03.03.20.
//

#ifndef ANTONGERDELAN_MOVER_H
#define ANTONGERDELAN_MOVER_H


#include <chrono>
#include "Object.h"
#include "old_code/Path.h"
#include "Chrono.h"

class Mover {
public:
    Mover(Object &obj, Path &path);
    glm::mat4 translation(float time);
    void draw(GLint uniTrans);
    void start();
    void pause();
private:
    Object &mObject;
    Path &mPath;
    Chrono mChrono;
};


#endif //ANTONGERDELAN_MOVER_H
