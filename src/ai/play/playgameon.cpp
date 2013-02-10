#include "playgameon.h"

PlayGameOn::PlayGameOn(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayGameOn", parent)
{
    _tg = new TacticGoalie(wm, kn, this);
    _rg = new RoleGoalie(this);

    _td1 = new TacticDefend(wm, kn, this);
    _td2 = new TacticDefend(wm, kn, this);
    _rd = new RoleDefender(this);

    _ta = new TacticAttack(wm, kn, this);

    _tb1 = new TacticBlock(wm, kn, this);
    _tb2 = new TacticBlock(wm, kn, this);
}

bool PlayGameOn::EnterCondition()
{
    if(_wm->cmgs.gameOn())
        return true;
    else
        return false;
}

bool PlayGameOn::ExecutePlayEngine()
{
    QList<int> agents = _kn->ActiveAgents();

    if(agents.count()<1) return true;

    // Goalie
    _tg->setRID(agents[0]);
    _sr->roles[agents[0]] = _rg;
    _sr->tactics[agents[0]] = _tg;
    _sr->useSkill[agents[0]] = false;

    if(agents.count()<2) return true;

    // Defender 1
    if(agents.count()==2)
        _td1->setTotalDef(1);
    else if(agents.count()>2)
        _td1->setTotalDef(2);
    _td1->setMyDef(1);
    _td1->setRID(agents[1]);
    _td1->defs[1] = agents[1];
    _sr->roles[agents[1]] = _rd;
    _sr->tactics[agents[1]] = _td1;
    _sr->useSkill[agents[1]] = false;

    if(agents.count()<3) return true;

    // Defender 2
    _td2->setRID(agents[2]);
    _td2->setTotalDef(2);
    _td2->setMyDef(2);
    _td2->defs[2] = agents[2];
    _sr->roles[agents[2]] = _rd;
    _sr->tactics[agents[2]] = _td2;
    _sr->useSkill[agents[2]] = false;

    if(agents.count()<4) return true;

    //Attacker
    _ta->setRID(agents[3]);
    _sr->tactics[agents[3]] = _ta;
    _sr->useSkill[agents[3]] = false;

    if(agents.count()<5) return true;

    //Block 1
    _tb1->setRID(agents[4]);
    if(agents.count()==5)
        _tb1->setTotalBlock(1);
    else
        _tb1->setTotalBlock(2);
    _tb1->setMyBlock(1);
    _sr->tactics[agents[4]] = _tb1;
    _sr->useSkill[agents[4]] = false;

    if(agents.count()<6) return true;

    //Block 2
    _tb2->setRID(agents[5]);
    _tb2->setMyBlock(2);
    _tb2->setTotalBlock(2);
    _sr->tactics[agents[5]] = _tb2;
    _sr->useSkill[agents[5]] = false;

    return true;
}
