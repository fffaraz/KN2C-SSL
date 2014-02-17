#ifndef SKILLGOTOPOSITION_H
#define SKILLGOTOPOSITION_H

#include <QObject>
#include "skill.h"
#include "skillmoveoncircle.h"
#include "navigationdefault.h"

class SkillGotoPosition : public Skill
{
    Q_OBJECT
public:
    SkillGotoPosition(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    bool done();

    void setPosition(const Position& Final, float Speed = 1);
    void setMaxDist(double maxdist) { _maxdist=maxdist; }
    void setName (QString name) { _name = name; }
    void setBallAsObstacle(bool ballAsObstacle) { _ballAsObstacle = ballAsObstacle; }

    bool checkPosition(Position);
protected:
    bool _ballAsObstacle;
    Position _FinalPos;
    float _Speed;
    double _maxdist;

private:
    NavigationDefault *_nav;
    SkillMoveOnCircle *_smoc;
};

#endif // SKILLGOTOPOSITION_H
