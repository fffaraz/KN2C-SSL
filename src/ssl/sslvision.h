#ifndef SSLVISION_H
#define SSLVISION_H

#include <QObject>
#include <QTime>

#include "messages_robocup_ssl_wrapper.pb.h"
#include "base.h"
#include "constants.h"
#include "sslreceiver.h"
#include "geom.h"
#include "visionframe.h"
#include "util.h"
#include "worldmodel.h"
#include "visionresult.h"

class SSLVision : public SSLReceiver
{
    Q_OBJECT

public:
    explicit SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, VisionResult* visionresult,QObject *parent = 0);

private:
    QTime _time;
    TeamColorType _color;
    TeamSideType _side;
    CameraConfigType _camera;
    FPSCounter _fpscam0;
    FPSCounter _fpscam1;
    VisionFrame _vframe [CAMERA_NUM]; // last frame read from each cameras
    VisionFrame _vmframe;  // then we merge both cameras into one vision frame
    VisionFrame _vrframe; // the result made from merged frame (vmframe) with only one instance for each vision object
    VisionResult* _vr; // the output

    void parse(SSL_DetectionFrame &pck);
    void merge();
    void updateresult();
    void updatewm();
    void fillframe(VisionFrame &frm, SSL_DetectionFrame &pck);
    void findClosestObject(VisionObject& vo, QList<VisionObject> list);

signals:
    void newVisionResult();

private slots:
    void readPendingPacket(QByteArray data, QString ip, int port);

};


//*180.0f/M_PI+(1.0-ourSide)*90.0f,rid));

#define APPEND_ROBOTS(__COLOR__,__TEAM__) \
for (int i=0; i<pck.robots_##__COLOR__##_size(); ++i) \
{ \
    int rid = pck.robots_##__COLOR__(i).robot_id(); \
    if (frm.__TEAM__##Robots[rid].count()>=VOBJ_MAX_NUM) continue; \
    if ((pck.robots_##__COLOR__(i).has_orientation())&&(pck.robots_##__COLOR__(i).has_confidence())&&(pck.robots_##__COLOR__(i).confidence()>MIN_CONF)&&(fabs(pck.robots_##__COLOR__(i).x())<FIELD_MAX_X)&&(fabs(pck.robots_##__COLOR__(i).y())<FIELD_MAX_Y)) \
    { \
        frm.__TEAM__##Robots[rid].append(VisionRobot(Vector2D(pck.robots_##__COLOR__(i).x()*ourSide, pck.robots_##__COLOR__(i).y()*ourSide), time, pck.robots_##__COLOR__(i).orientation()+(1.0-ourSide)*M_PI_2,rid)); \
        frm.notseen_##__TEAM__##Robot[rid] = 0; \
        seen_##__TEAM__[rid] = true; \
    } \
}

#define REMOVE_OLD_OBJECTS(__OBJECT__) \
    for(int i=0; i<_vrframe.__OBJECT__.count(); ++i) \
        if(cur_time - _vrframe.__OBJECT__[i].time > VISION_TIMEDOUT) \
            _vrframe.__OBJECT__.removeAt(i);

#define APPEND_NEW_OBJECTS(__OBJECT__) \
    _vrframe.__OBJECT__.append(_vmframe.__OBJECT__);



#define FIND_BEST_OBJ(__V__, __W__, __C__) \
if(_vrframe.__V__.count()==0) _vr->__W__.isValid=false; \
else \
{ \
    __C__ obj1(Vector2D(-10000,-10000)); \
    __C__ obj2(Vector2D(-10000,-10000)); \
    bool _ff=false; \
    for(int i=0; i<_vrframe.__V__.count(); ++i) \
    { \
        if((_vrframe.__V__[i].time>obj1.time) && ((_vrframe.__V__[i].pos - _vr->__W__.pos).length()<MAX_RADIOUS)) \
            {obj1 = _vrframe.__V__[i]; _ff=true;}\
        if((_vrframe.__V__[i].time==obj1.time) && ((_vrframe.__V__[i].pos - _vr->__W__.pos).length2()<(obj1.pos - _vr->__W__.pos).length2())) \
            {obj1 = _vrframe.__V__[i]; _ff=true;}\
        if((_vrframe.__V__[i].pos - _vr->__W__.pos).length2() < (obj2.pos - _vr->__W__.pos).length2()) \
            obj2 = _vrframe.__V__[i]; \
    } \
    _vr->__W__ = _ff?obj1:obj2; \
    _vr->__W__.isValid=true; \
}

#endif // SSLVISION_H
