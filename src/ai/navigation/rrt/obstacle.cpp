#include "obstacle.h"

int Obstacle::indexProvider = 0;

Obstacle::Obstacle(Region2D *region)
{
    _region = region;
    _index = Obstacle::indexProvider ++;
}

Region2D* Obstacle::region()
{
    return _region;
}

int Obstacle::index()
{
    return _index;
}
