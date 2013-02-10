#include "visionrecorder.h"

VisionRecorder::VisionRecorder(int buffersize, WorldModel* wm, QObject *parent) :
    FPSCounter(parent),
    _savedlist(),
    _wm(wm),
    _buffersize(buffersize),
    _state(false)
{
    // Log
    qDebug() << "VisionRecorder Initialization...";
    qDebug() << "Record Buffer: " << _buffersize;
}

void VisionRecorder::Start()
{
    qDebug() << "VisionRecorder::Start";
    _state=true;
}

void VisionRecorder::Stop()
{
    qDebug() << "VisionRecorder::Stop";
    _state=false;
}

WorldModel* VisionRecorder::getWM(int i)
{
    if(_savedlist.count()>i)
    {
        WorldModel* wmi;
        wmi = _savedlist.at(_savedlist.count()-1-i);
        return wmi;
    }
    else
    {
        WorldModel* nwm = new WorldModel();
        _savedlist.append(nwm);
        return _savedlist.last();
    }
}

void VisionRecorder::newWorldModel()
{
    //qDebug() << "NEW WORLD MODEL";
    if(_state) // if state == started...
    {

        if(_savedlist.count()>=_buffersize)
        {
            WorldModel* delwm = _savedlist.first();
            delete delwm;
            _savedlist.removeFirst();
        }
        WorldModel* nwm = new WorldModel();
        *nwm = *_wm;
        _savedlist.append(nwm);
        //qDebug()<< _savedlist.count();
        Pulse();
    }
}


