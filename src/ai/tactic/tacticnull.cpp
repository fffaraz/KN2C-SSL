#include "tacticnull.h"

TacticNull::TacticNull(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticNull", parent)
{
    _skillnull = new SkillNull(wm,this);
}

Skill* TacticNull::getSkill()
{
    _skillnull->setRID(_rid);
    return _skillnull;
}
