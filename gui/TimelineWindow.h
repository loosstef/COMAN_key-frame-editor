//
// Created by stef on 07.04.20.
//

#ifndef PROJECT_TIMELINEWINDOW_H
#define PROJECT_TIMELINEWINDOW_H

class Clock;

class TimelineWindow {
public:
    TimelineWindow(Clock *clock);
    void render();
private:
    Clock* mClock;
};


#endif //PROJECT_TIMELINEWINDOW_H
