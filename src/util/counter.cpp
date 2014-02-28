#include "counter.h"

Counter::Counter(QObject *parent, uint interval) :
    QObject(parent)
{
    totalcount = 0;
    pscounter = 0;
    pscounter_last = 0;

    connect(&timer,SIGNAL(timeout()), this, SLOT(timer_timeout()));
    if(interval < 1) this->interval = 1000;

    timer.setInterval(interval);
    timer.start();
}

void Counter::timer_timeout()
{
    pscounter_last = pscounter;
    pscounter = 0;
}

quint64 Counter::totalCount()
{
    return totalcount;
}

quint32 Counter::perSecond()
{
    return pscounter_last * (1000 / interval);
}

void Counter::pulse()
{
    totalcount++;
    pscounter++;
}
