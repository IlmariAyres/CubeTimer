#ifndef TIMER_H
#define TIMER_H

#include "timec.h"

#include <QElapsedTimer>

class Timer
{
public:
    void startInspection();
    void stopInspection();

    void startTimer();
    void stopTimer();
    TimeC getTime();

    void setInspection(int i);
    void reset();
    TimeState getState();

private:
    int inspection;
    TimeC time;

    QElapsedTimer qtimer;

    TimeState state = STATE_INITIAL;
};

#endif // TIMER_H
