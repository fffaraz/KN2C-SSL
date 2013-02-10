#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H

#include "geom.h"
#include "position.h"

class MobileObject
{
public:
    explicit MobileObject();
    double time;
    bool isValid;
    Position pos;
    Position vel;
};

#endif // MOBILEOBJECT_H
