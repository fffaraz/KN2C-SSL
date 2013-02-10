#ifndef VISIONRECORDER_H
#define VISIONRECORDER_H

#include <QObject>
#include <QLinkedList>
#include "worldmodel.h"
#include "fpscounter.h"

class VisionRecorder : public FPSCounter
{
    Q_OBJECT
public:
    explicit VisionRecorder(int buffersize, WorldModel* wm, QObject *parent = 0);

signals:

public slots:
    void newWorldModel();
    void Start();
    void Stop();
    WorldModel* getWM(int i);

private:
    QList<WorldModel*> _savedlist;
    WorldModel* _wm;
    int _buffersize;
    bool _state;
};

#endif // VISIONRECORDER_H
