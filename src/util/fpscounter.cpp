#include "fpscounter.h"

FPSCounter::FPSCounter(QObject *parent, uint fpsinterval) :
    QObject(parent),
    _totalcounter(0),
    _fpscounter(0),
    _lastfps(0),
    _resettimer(parent),
    _fpsinterval(fpsinterval)
{
    connect(&_resettimer,SIGNAL(timeout()), this, SLOT(resetFPSCounter()));
    if(_fpsinterval < 1) _fpsinterval = 1000;
    _resettimer.setInterval(_fpsinterval);
    _resettimer.start();
}

void FPSCounter::resetFPSCounter()
{
    _lastfps=_fpscounter;
    //_lastfps_val = _lastfps * (1000 / _fpsinterval);
    _fpscounter=0;
}

quint64 FPSCounter::TotalCounter()
{
    return _totalcounter;
}

quint32 FPSCounter::FPS()
{
    _lastfps_val = _lastfps * (1000 / _fpsinterval);
    return _lastfps_val;
}

void FPSCounter::Pulse()
{
    _totalcounter++;
    _fpscounter++;
}
