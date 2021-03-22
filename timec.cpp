#include "timec.h"

#include <QStringBuilder>

TimeC::TimeC(int t, TimeState s)
{
    time = t;
    state = s;
}


QString TimeC::getQStr()
{
    if(time < 0)
        return QString("DNF");
    else if(state == STATE_INSPECTING)
        return QString("%1").arg(time);
    else
        return QString("%1:%2.%3").arg(time / 60000, 2, 10, QChar('0')).arg((time % 60000) / 1000, 2, 10, QChar('0')).arg((time % 1000) / 10, 2, 10, QChar('0'));
}

QString TimeC::getQStr(int t)
{
    TimeC time(t);
    return time.getQStr();
}
