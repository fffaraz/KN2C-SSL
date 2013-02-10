#include "skillballtracking.h"

SkillBallTracking::SkillBallTracking(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillBallTracking", parent),
    _maxdist(0)
{
    _face=Vector2D(0,0);
}

bool SkillBallTracking::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;
    rc.FinalPos.loc=_wm->ball.pos.loc;
    rc.TargetPos.loc=_wm->ball.pos.loc;
    rc.FinalPos.dir = (_face - _wm->ourRobot[_rid].pos.loc).dir().radian();
    rc.TargetPos.dir = (_face - _wm->ourRobot[_rid].pos.loc).dir().radian();

    rc.Speed=1;
    return true;
}

bool SkillBallTracking::SkillDone()
{
    if((_wm->ourRobot[_rid].pos.loc-_wm->ball.pos.loc).length()<_maxdist)
        return true;
    else return false;
}

