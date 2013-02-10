#include "strategy.h"
#include "playnull.h"
#include "rolenull.h"
#include "skillnull.h"

Strategy::Strategy(WorldModel *wm, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _wm(wm)
{
    _result.play = new PlayNull(wm, &_result, 0, this);
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        _result.useSkill[i] = false;
        _result.roles[i] = new RoleNull(this);
        _result.tactics[i] = new TacticNull(wm, 0, this);
        _result.skills[i] = new SkillNull(wm, this);
    }
}

Skill* Strategy::getSkill(int rid)
{
    if(_result.useSkill[rid])
        return _result.skills[rid];
    else
        return _result.tactics[rid]->getSkill();
}
