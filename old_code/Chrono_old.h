//
// Created by stef on 04.03.20.
//

#ifndef ANTONGERDELAN_CHRONO_H
#define ANTONGERDELAN_CHRONO_H


#include <ctime>

class Chrono_old {
public:
    void reset();
    void start();
    void pause();
    double getTime();
private:
    double mTime = 0;
    double mMomentOfLastUpdate;
    bool mRunning = false;
};


#endif //ANTONGERDELAN_CHRONO_H
