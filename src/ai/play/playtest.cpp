#include "playtest.h"

PlayTest::PlayTest(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayTest", parent)
{
    _tt = new TacticTest(wm, kn, this);
    _ta= new TacticAttack(wm, kn, this);
}

bool PlayTest::EnterCondition()
{
    return true;
}

bool PlayTest::ExecutePlayEngine()
{
    QList<int> agents = _kn->ActiveAgents();
    if(agents.count()<1) return true;
    _ta->setRID(agents[0]);
    _sr->tactics[agents[0]] = _ta;
    _sr->useSkill[agents[0]]= false;
    return true;
}
