#include "skillturntoangle.h"


SkillTurnToAngle::SkillTurnToAngle(WorldModel *wm, QObject *parent)
    : Skill(wm, "SkillTurnToAngle", parent)
{
    this->_done = false;
}

bool SkillTurnToAngle::execute(RobotCommand &rc)
{
    Position pos;
    pos.dir = _target;
    pos.loc = _wm->ourRobot[_rid].pos.loc;

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

bool SkillTurnToAngle::done()
{
    return this->_done;
}
