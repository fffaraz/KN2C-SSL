#ifndef VISIONTRACKER_H
#define VISIONTRACKER_H

#include <QObject>
#include "visionresult.h"
#include "worldmodel.h"
#include "visionrecorder.h"

class VisionTracker : public QObject
{
    Q_OBJECT
public:
    explicit VisionTracker(VisionResult* vr, WorldModel* wm, VisionRecorder* recorder, QObject *parent = 0);

private:
    VisionResult* _vr;
    WorldModel* _wm;
    VisionRecorder* _recorder;
    bool _state;

    Position getOurRobotSpeed(int rid);
    Position getOppRobotSpeed(int rid);
    Position getBallSpeed();

signals:
    void newWorldModel();

public slots:
    void newVisionResult();
    void Start();
    void Stop();

};

#endif // VISIONTRACKER_H
