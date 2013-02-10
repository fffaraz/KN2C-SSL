#ifndef NAVIGATIONDEFAULT_H
#define NAVIGATIONDEFAULT_H

#include <QObject>
#include "navigation.h"

class NavigationDefault : public Navigation
{
    Q_OBJECT
public:
    explicit NavigationDefault(WorldModel* wm, QObject *parent = 0);
    bool execute(int rid, Position FinalPos, Position& TargetPos);
private:
    bool intersectOBS(Vector2D robotOBSloc,Vector2D cur,Vector2D dest);
    Vector2D robotLoc(int rid,bool ourRobot);
signals:

public slots:

};

#endif // NAVIGATIONDEFAULT_H
