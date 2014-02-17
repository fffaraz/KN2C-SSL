#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "geom/region_2d.h"

#include "geom/circle_2d.h"
#include "geom/rect_2d.h"
#include "geom/triangle_2d.h"

#include <QList>

using namespace rcsc;

class Obstacle
{
    /** Private Field Members */
private:
    int _index;
    Region2D *_region;

    /** Static Field Members */
public:
    static int indexProvider;

    /** Indexers */
public:
    Region2D* region();
    int index();

    /** Constructors */
public:
    Obstacle(Region2D* region);
};

typedef QList<Obstacle*> Obstacles;

#endif // OBSTACLE_H
