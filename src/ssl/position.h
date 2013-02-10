#ifndef POSITION_H
#define POSITION_H

#include "geom.h"

struct Position
{
    Vector2D loc;   // Location
    float dir;      // Direction
    Position()
    {
        loc=Vector2D(0,0);
        dir=0;
    }
};

#endif // POSITION_H
