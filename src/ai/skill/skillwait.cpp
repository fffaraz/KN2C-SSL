#include "skillwait.h"

SkillWait::SkillWait(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillWait", parent),
    _qtime(),
    _time(0)
{
    _elapsed=_qtime.elapsed();
}

bool SkillWait::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;
    rc.FinalPos=_Pos;
    rc.TargetPos=_Pos;
    rc.Speed=1;
    return true;
}

void SkillWait::setPosition(const Position &Final)
{
    _Pos=Final;
}

bool SkillWait::SkillDone()
{
    if(_qtime.elapsed()>_elapsed+_time)
        return true;
    else return false;
}

void SkillWait::ResetTime()
{
    _elapsed=_qtime.elapsed();
}
