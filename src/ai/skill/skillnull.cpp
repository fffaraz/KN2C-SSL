#include "skillnull.h"

SkillNull::SkillNull(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillNull", parent)
{
}

bool SkillNull::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;
    rc.FinalPos=Position();
    rc.TargetPos=Position();
    rc.Speed=0;
    return false;
}

bool SkillNull::SkillDone()
{
    return true;
}
