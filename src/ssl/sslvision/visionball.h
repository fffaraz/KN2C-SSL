#ifndef VISIONBALL_H
#define VISIONBALL_H

#include "visionobject.h"

class VisionBall : public VisionObject
{
public:
    explicit VisionBall(Vector2D Pos = Vector2D(0,0), double Time = 0) :
        VisionObject(Pos, Time)
    { }
};

#endif // VISIONBALL_H
