#include "playstop.h"

PlayStop::PlayStop(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayStop", parent)
{
    _ts1 = new TacticStop(wm, kn, this);
    _ts2 = new TacticStop(wm, kn, this);
    _ts3 = new TacticStop(wm, kn, this);
    _tg  = new TacticGoalie(wm, kn, this);
    _td1 = new TacticDefend(wm, kn, this);
    _td2 = new TacticDefend(wm, kn, this);
    _rg = new RoleGoalie(this);
    _rd = new RoleDefender(this);
}

bool PlayStop::EnterCondition()
{
    if(_wm->gs == STATE_Stop)
        return true;
    else
        return false;
}

bool PlayStop::ExecutePlayEngine()
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

    // Stop 1
    if(agents.count()==4)
        _ts1->setTotalStop(1);
    else if(agents.count()==5)
        _ts1->setTotalStop(2);
    else if(agents.count()>5)
        _ts1->setTotalStop(3);
    _ts1->setMyStop(1);
    _ts1->setRID(agents[3]);
    _ts1->setTarget(_wm->ball.pos.loc,Vector2D(-3010,0),700,true);

    _sr->tactics[agents[3]] = _ts1;
    _sr->useSkill[agents[3]] = false;

    if(agents.count()<5) return true;

    // Stop 2
    if(agents.count()==5)
        _ts2->setTotalStop(2);
    else if(agents.count()==5)
        _ts2->setTotalStop(3);
    _ts2->setMyStop(2);
    _ts2->setRID(agents[4]);
    _ts2->setTarget(_wm->ball.pos.loc,Vector2D(-3010,0),700,true);
    _sr->tactics[agents[4]] = _ts2;
    _sr->useSkill[agents[4]] = false;

    if(agents.count()<6) return true;

    // Stop 3
    _ts3->setTotalStop(3);
    _ts3->setMyStop(3);
    _ts3->setRID(agents[5]);
    _ts3->setTarget(_wm->ball.pos.loc,Vector2D(-3010,0),700,true);
    _sr->tactics[agents[5]] = _ts3;
    _sr->useSkill[agents[5]] = false;


    return true;
}

