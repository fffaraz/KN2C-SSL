#include "tacticattack.h"

TacticAttack::TacticAttack(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticAttack", parent)
{
    _kick = new SkillKick(wm, this);
}

Skill* TacticAttack::getSkill()
{
    _kick->setTarget(Vector2D(3025,0));
    _kick->setRID(_rid);
    return _kick;
}

