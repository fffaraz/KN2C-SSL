#include "skillturntopoint.h"

SkillTurnToPoint::SkillTurnToPoint(WorldModel *wm, QObject *parent)
    : Skill(wm, "SkillTurnToPoint", parent)
{
    this->_done = false;
}

bool SkillTurnToPoint::execute(RobotCommand &rc)
{
    Position pos;
    pos.loc = _target;
    pos.dir = (_target - _wm->ourRobot[_rid].pos.loc).dir().radian();

    if (fabs(pos.dir - _wm->ourRobot[_rid].pos.dir) < M_PI / 36.0) // 5.0 degree
    {
        this->_done = true;
        return false;
    }

    this->_done = false;

    rc.FinalPos = rc.TargetPos = pos;
    rc.kickspeedx = rc.kickspeedz = 0;
    rc.Speed = 1;

    return true;
}

bool SkillTurnToPoint::done()
{
    return this->_done;
}
