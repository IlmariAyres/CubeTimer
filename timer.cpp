#include "timer.h"

void Timer::startTimer()
{
    qtimer.start();
    state = STATE_RUNNING;
}

void Timer::stopTimer()
{
    time.time = qtimer.elapsed();
    state = STATE_FINAL;
    qtimer.invalidate();
}

void Timer::startInspection()
{
    state = STATE_INSPECTING;
    qtimer.start();
}

void Timer::stopInspection()
{
    state = STATE_STOPPED;
    qtimer.invalidate();
    time.time = 0;
}

void Timer::setInspection(int i)
{
    if(i >= 0)
        inspection = i;
}

void Timer::reset()
{
    qtimer.invalidate();
    state = STATE_INITIAL;
    time.time = 0;
}

TimeState Timer::getState()
{
    return state;
}

TimeC Timer::getTime()
{
    time.state = state;

    switch(state)
    {
    case STATE_INITIAL:
        time.state = STATE_INITIAL;
        time.time = 0;
        break;
    case STATE_INSPECTING:
        if(inspection * 1000 > qtimer.elapsed())
        {
            time.state = STATE_INSPECTING;
            time.time = inspection - (qtimer.elapsed() / 1000);
        }
        else
        {
            stopInspection();
            startTimer();
            return getTime();
        }
        break;
    case STATE_RUNNING:
        time.state = STATE_RUNNING;
        time.time = qtimer.elapsed();
        break;
    }

    return time;
}
