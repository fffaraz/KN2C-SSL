#include "skillgotoposition.h"

SkillGotoPosition::SkillGotoPosition(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillGotoPosition", parent),
    _maxdist(0)
{
    _ballAsObstacle = false;
    _FinalPos = Position();
    _Speed = 1;
    _smoc = new SkillMoveOnCircle(wm, this);
    _nav = new NavigationDefault(wm, this);
    _nav->createRRTPlanners();
}

bool SkillGotoPosition::execute(RobotCommand &rc)
{
    if(_rid==-1)
        return false;

    Position position;
    float speed;
    _nav->execute(_rid, _FinalPos, position, speed, _ballAsObstacle);

    if (_rid != GOALIE_ID && checkPosition(rc.TargetPos))
    {
        _smoc->setCenter(Vector2D(-FIELD_MAX_X, 0));
        _smoc->setEnd(_wm->ourRobot[_rid].pos.loc);
        _smoc->setTarget(position.loc);
        _smoc->setRadius(990 + ROBOT_RADIUS);
        _smoc->setRID(_rid);
        _smoc->execute(rc);
    }
    else
    {
        rc.TargetPos = position;
        rc.FinalPos = _FinalPos;
        rc.Speed = _Speed;
    }

    return true;
}

bool SkillGotoPosition::checkPosition(Position target)
{
    Segment2D segment (_wm->ourRobot[_rid].pos.loc, target.loc);
    Circle2D circle (Vector2D(-FIELD_MAX_X, 0), 1000);
    Vector2D sol1, sol2;

    int intersect = circle.intersection(segment, &sol1, &sol2);

    if (intersect == 0)
        return false;

    return true;
}

void SkillGotoPosition::setPosition(const Position &Final, float Speed)
{
    _FinalPos=Final;
    _Speed=Speed;
}

bool SkillGotoPosition::done()
{
    if((_wm->ourRobot[_rid].pos.loc-_FinalPos.loc).length()<_maxdist)
    {
        return true;
    }
    else
    {
        return false;
    }
}
