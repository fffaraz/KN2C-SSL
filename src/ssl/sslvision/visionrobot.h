#ifndef VISIONROBOT_H
#define VISIONROBOT_H

#include "visionobject.h"

class VisionRobot : public VisionObject
{
public:
    float angle;
    int id;
    explicit VisionRobot(Vector2D Pos = Vector2D(0,0), double Time = 0, float Angle = 0, int ID = -1):
        VisionObject(Pos, Time),
        angle(Angle),
        id(ID)
    { }
};

#endif // VISIONROBOT_H
