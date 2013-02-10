#include "playpenaltyour.h"

PlayPenaltyOur::PlayPenaltyOur(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayPenaltyOur", parent),
    _cankick(false)
{
    _ta = new TacticAttack(wm, kn, this);
    _ts1 = new TacticStop(wm, kn, this);
    _ts2 = new TacticStop(wm, kn, this);
    _ts3 = new TacticStop(wm, kn, this);
    _ts4 = new TacticStop(wm, kn, this);
    _ts5 = new TacticStop(wm, kn, this);
    _ts6 = new TacticStop(wm, kn, this);
}

bool PlayPenaltyOur::EnterCondition()
{
    if(_wm->cmgs.ourPenaltyKick() && _wm->cmgs.canKickBall()==_cankick)
        return true;
    else
        return false;
}

bool PlayPenaltyOur::ExecutePlayEngine()
{
    QList<int> agents = _kn->ActiveAgents();

    if(agents.count()<1) return true;

    if(_cankick)
    {
        _ta->setRID(agents[0]);
        _sr->tactics[agents[0]] = _ta;
        _sr->useSkill[agents[0]] = false;
    }
    else
    {
        _ts1->setRID(agents[0]);
        _ts1->setMyStop(1);
        _ts1->setTotalStop(1);
        _ts1->setTarget(_wm->ball.pos.loc, Vector2D(3025,200), 120, false);
        _sr->tactics[agents[0]] = _ts1;
        _sr->useSkill[agents[0]] = false;
    }

    if(agents.count()<2) return true;

    // Stop 1
    _ts6->setTotalStop(1);
    _ts6->setMyStop(1);
    _ts6->setRID(agents[1]);
    _ts6->setTarget(Vector2D(-1500,0),Vector2D(-1500,100),500,true);

    _sr->tactics[agents[1]] = _ts6;
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

