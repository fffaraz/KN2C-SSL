#ifndef VISIONOBJECT_H
#define VISIONOBJECT_H

#include "messages_robocup_ssl_detection.pb.h"
#include "geom.h"

class VisionObject
{

public:
    bool isValid;
    Vector2D pos;
    double time;
    explicit VisionObject(Vector2D Pos, double Time) :
        isValid(true),
        pos(Pos),
        time(Time)
    { }
};

#endif // VISIONOBJECT_H
