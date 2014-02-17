#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <QObject>
#include "worldmodel.h"
#include "constants.h"
#include "math.h"

class Knowledge : public QObject
{
    Q_OBJECT
public:
    explicit Knowledge(WorldModel* wm, QObject *parent = 0);

    int countActiveAgents();
    int countActiveRoles();

    int ballKicker();
    int findNearestOpponentToBall();
    int findNearestTeammateToPointByStaticPosition(Vector2D point, PlayMode pm = GameOn);
    int findNearestTeammateToPoint(Vector2D point);
    int findOpponentKicker();

    QList<int> activeAgents();
    QList<int> findRole(QString name);
    QList<int> findNearestTo(Vector2D loc);

    Vector2D findNearestPositionToRobot(QList <Vector2D> positions , int rid);

    bool findNearestPointToDummy(Vector2D point,int rid);
    bool isBallKickable(int Rid);
    bool isGoalieValid();

    bool isInPenaltyArea(Vector2D vec);

private:
    WorldModel* _wm;

public:
    bool validGoalie;

signals:

public slots:

};

#endif // KNOWLEDGE_H
