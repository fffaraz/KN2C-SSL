#include "skillcircle.h"

SkillCircle::SkillCircle(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillCircle", parent)
{
    radius=0;
}

bool SkillCircle::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;
    Vector2D vc;
    vc = _wm->ourRobot[_rid].pos.loc;
    vc.setLength(500);
    vc.rotate(10);
    rc.FinalPos.loc=vc;
    rc.TargetPos.loc=vc;
    rc.FinalPos.dir=(_wm->ball.pos.loc - _wm->ourRobot[_rid].pos.loc).dir().radian();
    rc.TargetPos.dir=(_wm->ball.pos.loc - _wm->ourRobot[_rid].pos.loc).dir().radian();
    rc.Speed=1;
    return true;
}

bool SkillCircle::SkillDone()
{
    return false;
}
