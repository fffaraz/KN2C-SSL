#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticGoalie", parent)
{
    _skill = new SkillGoalie(wm, this);
    _skillp = new SkillGoaliePenalty(wm, this);
    _penalty=false;
}

Skill* TacticGoalie::getSkill()
{
    _skill->setRID(_rid);
    _skillp->setRID(_rid);
    if(!_penalty)
        return _skill;
    else return _skillp;
}
