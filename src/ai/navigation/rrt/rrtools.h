#ifndef RRTOOLS_H
#define RRTOOLS_H

#include <QList>
#include "obstacle.h"
#include "geom/vector_2d.h"

class RRTools
{
public:
    template <typename T>
    static int sign(T val) {
        return val == 0 ? 0 : ( val > 0 ? 1 : -1 );
    }

    static bool contains(QList<Obstacle*> regions, Vector2D vec)
    {
        foreach(Obstacle* region, regions)
            if (region->region()->contains(vec))
                return true;

        return false;
    }

};

#endif // RRTOOLS_H
