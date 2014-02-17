#ifndef NAVIGATIONDEFAULT_H
#define NAVIGATIONDEFAULT_H

#include <QObject>
#include "navigation.h"
#include "rrt/rrtplan.h"

class NavigationDefault : public Navigation
{
    Q_OBJECT
public:
    explicit NavigationDefault(WorldModel* wm , QObject *parent = 0);
    bool execute(int rid, Position FinalPos, Position &Solution, float &RobotSpeed, bool ballAsObstacle = true);

public:
    void createRRTPlanners()
    {
        _plannerGoalInit = new RRTPlan(5,
                                       0, 6050,
                                       0, 4050,
                                       new Vector2D(Vector2D::INVALIDATED),
                                       new Vector2D(Vector2D::INVALIDATED));
        _plannerInitGoal = new RRTPlan(5,
                                       0, 6050,
                                       0, 4050,
                                       new Vector2D(Vector2D::INVALIDATED),
                                       new Vector2D(Vector2D::INVALIDATED));
    }

private:
    RRTPlan *_plannerInitGoal;
    RRTPlan *_plannerGoalInit;

signals:

public slots:

};

#endif // NAVIGATIONDEFAULT_H
