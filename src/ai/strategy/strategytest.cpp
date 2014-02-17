#include "strategytest.h"
#include "skillgotoposition.h"

StrategyTest::StrategyTest(WorldModel *wm, QMap<int, Agent *> &agents, QObject *parent) :
    Strategy(wm, agents, "StrategyDefault", parent),
    _knowledge(wm)
{
    wm->sixNormalFormation->createFormationTable(_wm->playMode());/*
    wm->sixFreeKickFormation->createFormationTable(_wm->playMode());*/

    wm->fiveNormalFormation->createFormationTable(_wm->playMode());/*
    wm->fiveFreeKickFormation->createFormationTable(_wm->playMode());*/
}

bool StrategyTest::ExecuteStrategyEngine()
{
    // DO WHAT THE FUCK YOU WANT HERE !
    // YOU HAVE ACCESS TO _wm AND _agents
    // You have to update _agents[x]->rc
    //    if(_wm->getPlayMode()==GameOn)
    //    {
    //        Skill *skill = new GotoPosition(_wm);
    //        skill->setRID(0);
    //    }
    //    Position p;
    //    if (_wm->goalsOur() > _wm->goalsOpp())
    //    {
    //        p.loc.x = 1000;
    //        p.loc.y = 1000;
    //        _agents[0]->rc.TargetPos = p;
    //        _agents[0]->rc.FinalPos = p;
    //    }
    //    else
    //    {
    //    }
    //    logger.log("StrategyDefault");
    //    p.loc.x = -2800;
    //    p.loc.y = 0;
    //    _agents[0]->rc.FinalPos = p;
    //    _agents[0]->rc.TargetPos = p;
    //    p.loc.x = -2500;
    //    p.loc.y = 200;
    //    _agents[1]->rc.FinalPos = p;
    //    _agents[1]->rc.TargetPos = p;
    //    p.loc.x = -2500;
    //    p.loc.y = -200;
    //    _agents[2]->rc.FinalPos = p;
    //    _agents[2]->rc.TargetPos = p;
    //    p.loc.x = -1500;
    //    p.loc.y = -1000;
    //    _agents[3]->rc.FinalPos = p;
    //    _agents[3]->rc.TargetPos = p;
    //    p.loc.x = -1500;
    //    p.loc.y = 1000;
    //    _agents[4]->rc.FinalPos = p;
    //    _agents[4]->rc.TargetPos = p;
    //    p.loc.x = -50;
    //    p.loc.y = 0;
    //    _agents[5]->rc.FinalPos = p;
    //    _agents[5]->rc.TargetPos = p;

    //    if (_wm->cmgs.kickoff())
    //    {
    //        Position p;
    //        p.loc.x = 1000;
    //        p.loc.y = 1000;
    //        _agents[1]->rc.FinalPos = p;
    //        _agents[1]->rc.TargetPos = p;
    //    }
    //    if (_wm->cmgs.gameOn())
    //    {
    //        Position p;
    //        p.loc.x = -5000;
    //        p.loc.y = 0;
    //        _agents[0]->rc.FinalPos= p;
    //        p.loc.x = -3500;
    //        p.loc.y = -500;
    //        _agents[1]->rc.FinalPos= p;
    //        p.loc.x = -3500;
    //        p.loc.y = 500;
    //        _agents[2]->rc.FinalPos= p;
    //        p.loc.x = -1500;
    //        p.loc.y = 500;
    //        _agents[3]->rc.FinalPos= p;
    //        p.loc.x = -1500;
    //        p.loc.y = 500;
    //        _agents[4]->rc.FinalPos= p;
    //        p.loc.x = -50;
    //        p.loc.y = 0;
    //        _agents[5]->rc.FinalPos= p;
    //    }





    return 0;
}

