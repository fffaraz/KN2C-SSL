#include "skillgotoposition.h"

SkillGotoPosition::SkillGotoPosition(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillGotoPosition", parent),
    _nav(wm, parent),
    _maxdist(0)
{
    _FinalPos=Position();
    _Speed=1;
}

bool SkillGotoPosition::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;
    rc.FinalPos=_FinalPos;
    _nav.execute(_rid, _FinalPos, rc.TargetPos);
    //rc.TargetPos=_FinalPos;
    rc.Speed=_Speed;
    return true;
}

void SkillGotoPosition::setPosition(const Position &Final, float Speed)
{
    _FinalPos=Final;
    _Speed=Speed;
}

bool SkillGotoPosition::SkillDone()
{
    if((_wm->ourRobot[_rid].pos.loc-_FinalPos.loc).length()<_maxdist)
        return true;
    else return false;
}
