#include "playpenaltyopp.h"

PlayPenaltyOpp::PlayPenaltyOpp(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayPenaltyOpp", parent)
{
    _tg = new TacticGoalie(wm, kn, this);
    _rg = new RoleGoalie(this);

    _ts1 = new TacticStop(wm, kn, this);
    _ts2 = new TacticStop(wm, kn, this);
    _ts3 = new TacticStop(wm, kn, this);
    _ts4 = new TacticStop(wm, kn, this);
    _ts5 = new TacticStop(wm, kn, this);
}

bool PlayPenaltyOpp::EnterCondition()
{
    if(_wm->cmgs.theirPenaltyKick())
        return true;
    else
        return false;
}

bool PlayPenaltyOpp::ExecutePlayEngine()
{
    QList<int> agents = _kn->ActiveAgents();

    if(agents.count()<1) return true;

    // Goalie
    _tg->setRID(agents[0]);
    _tg->setPenalty(true);
    _sr->roles[agents[0]] = _rg;
    _sr->tactics[agents[0]] = _tg;
    _sr->useSkill[agents[0]] = false;

    if(agents.count()<2) return true;

    // Stop 1
    _ts1->setTotalStop(1);
    _ts1->setMyStop(1);
    _ts1->setRID(agents[1]);
    _ts1->setTarget(Vector2D(-1500,0),Vector2D(-1500,100),500,true);

    _sr->tactics[agents[1]] = _ts1;
    _sr->useSkill[agents[1]] = false;

    if(agents.count()<3) return true;

    // Stop 2
    _ts2->setTotalStop(1);
    _ts2->setMyStop(1);
    _ts2->setRID(agents[2]);
    _ts2->setTarget(Vector2D(-1500,0),Vector2D(-1500,100),500,false);

    _sr->tactics[agents[2]] = _ts2;
    _sr->useSkill[agents[2]] = false;

    if(agents.count()<4) return true;

    // Stop 3
    _ts3->setTotalStop(1);
    _ts3->setMyStop(1);
    _ts3->setRID(agents[3]);
    _ts3->setTarget(Vector2D(-1000,0),Vector2D(-1000,100),500,false);

    _sr->tactics[agents[3]] = _ts3;
    _sr->useSkill[agents[3]] = false;

    if(agents.count()<5) return true;

    // Stop 4
    _ts4->setTotalStop(1);
    _ts4->setMyStop(1);
    _ts4->setRID(agents[4]);
    _ts4->setTarget(Vector2D(-1000,0),Vector2D(-1000,100),500,true);

    _sr->tactics[agents[4]] = _ts4;
    _sr->useSkill[agents[4]] = false;

    if(agents.count()<6) return true;

    // Stop 5
    _ts5->setTotalStop(1);
    _ts5->setMyStop(1);
    _ts5->setRID(agents[5]);
    _ts5->setTarget(Vector2D(-1250,0),Vector2D(0,0),500,true);

    _sr->tactics[agents[5]] = _ts5;
    _sr->useSkill[agents[5]] = false;

    return true;
}

