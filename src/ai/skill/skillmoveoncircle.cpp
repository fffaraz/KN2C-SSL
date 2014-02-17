#include "skill/skillmoveoncircle.h"

SkillMoveOnCircle::SkillMoveOnCircle(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillMoveOnCircle", parent)
{
    _radius = 0;
}

bool SkillMoveOnCircle::execute(RobotCommand &rc)
{
    if(_rid == -1)
        return false;

    Vector2D vec = _center;
    Vector2D selfRel = _end - _center;
    AngleDeg selfRelAngle = selfRel.dir();

    Vector2D targetRel = _target - _center;
    AngleDeg targetRelAngle = targetRel.dir();

    AngleDeg angleDiff = targetRelAngle - selfRelAngle;

    if (angleDiff.abs() > 30)
    {
        vec.x += _radius * cos(selfRelAngle.radian() + 30 * AngleDeg::DEG2RAD * (angleDiff.degree() > 0 ? 1 : -1));
        vec.y += _radius * sin(selfRelAngle.radian() + 30 * AngleDeg::DEG2RAD * (angleDiff.degree() > 0 ? 1 : -1));
    }
    else
    {
        vec.x += _radius * cos(targetRelAngle.radian());
        vec.y += _radius * sin(targetRelAngle.radian());
    }

    rc.FinalPos.loc = _target;
    rc.TargetPos.loc = vec;
    rc.FinalPos.dir = (_wm->ball.pos.loc - _wm->ourRobot[_rid].pos.loc).dir().radian();
    rc.TargetPos.dir = (_wm->ball.pos.loc - _wm->ourRobot[_rid].pos.loc).dir().radian();
    rc.Speed=1;

    return true;
}

bool SkillMoveOnCircle::done()
{
    return false;
}
