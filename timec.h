#ifndef TIMEC_H
#define TIMEC_H

#include <QString>

enum TimeState { STATE_STATELESS, STATE_INITIAL, STATE_INSPECTING, STATE_RUNNING, STATE_STOPPED, STATE_FINAL };

class TimeC
{
public:
    TimeC(int t = 0, TimeState s = STATE_STATELESS);

    QString getQStr();
    static QString getQStr(int t);

    TimeState state = STATE_INITIAL;
    int time = 0;
};

#endif // TIMEC_H
