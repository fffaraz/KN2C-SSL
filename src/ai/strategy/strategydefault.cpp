#include "strategydefault.h"

StrategyDefault::StrategyDefault(WorldModel *wm, QMap<int, Agent *> &agents, QObject *parent) :
    Strategy(wm, agents, "StrategyDefault", parent),
    _knowledge(wm)
{
    robotNum = _knowledge.countActiveAgents();

    wm->sixNormalFormation->createFormationTable(GameOn);
    wm->sixFreeKickOurFormation->createFormationTable(DirectFreeKickOur);
    wm->sixFreeKickOppFormation->createFormationTable(DirectFreeKickOpp);

    wm->fiveNormalFormation->createFormationTable(GameOn);
    wm->fiveFreeKickOurFormation->createFormationTable(DirectFreeKickOur);
    wm->fiveFreeKickOppFormation->createFormationTable(DirectFreeKickOpp);

    qDebug() << wm->sixNormalFormation->M_sample_vector->size();
    qDebug() << wm->fiveNormalFormation->M_sample_vector->size();
    qDebug() << wm->sixFreeKickOurFormation->M_sample_vector->size();
    qDebug() << wm->sixFreeKickOppFormation->M_sample_vector->size();
    qDebug() << wm->fiveFreeKickOurFormation->M_sample_vector->size();
    qDebug() << wm->fiveFreeKickOppFormation->M_sample_vector->size();

    _firstTimeFlag = true;

    _tg = new TacticGoalie(_wm,&_knowledge);
    _tlb = new TacticLeftBack(_wm,&_knowledge);
    _trb = new TacticRightBack(_wm,&_knowledge);
    _tcb = new TacticCenterBack(_wm,&_knowledge);
    _tcm = new TacticCenterMidfielder(_wm,&_knowledge);
    _tlf = new TacticLeftForward(_wm,&_knowledge);
    _trf = new TacticRightForward(_wm,&_knowledge);
    _tcf = new TacticCenterForward(_wm,&_knowledge);
    _validTactics3.append(_tg->Name());
    _validTactics3.append(_tlb->Name());
    _validTactics3.append(_trb->Name());

    _validTactics4.append(_tg->Name());
    _validTactics4.append(_tlb->Name());
    _validTactics4.append(_trb->Name());
    _validTactics4.append(_tcm->Name());

    _validTactics5.append(_tg->Name());
    _validTactics5.append(_tlb->Name());
    _validTactics5.append(_trb->Name());
    _validTactics5.append(_tcm->Name());
    _validTactics5.append(_tcf->Name());

    _validTactics6.append(_tg->Name());
    _validTactics6.append(_tlb->Name());
    _validTactics6.append(_trb->Name());
    _validTactics6.append(_tcm->Name());
    _validTactics6.append(_tlf->Name());
    _validTactics6.append(_trf->Name());
}

bool StrategyDefault::ExecuteStrategyEngine()
{
    if (_knowledge.countActiveAgents()==0)
        return false;
    if(_firstTimeFlag)
    {
        robotNum = _knowledge.countActiveAgents();
        if (_wm->ourRobot[GOALIE_ID].isValid)
        {
            _tg->setRID(GOALIE_ID);
            _agents[GOALIE_ID]->assignTactic(_tg);
            _knowledge.validGoalie = true;
        }
        else
        {
            _knowledge.validGoalie = false;
            _agents[GOALIE_ID]->assignTactic(0);
        }
        QList <Vector2D> staticPositions;
        int roles = _knowledge.countActiveRoles();
        if (roles > 2)
            for(int cnt = 1 ; cnt<roles ; cnt++)
                staticPositions.append(_wm->position(cnt,roles,_wm->ball.pos.loc, GameOn));
        QList <Vector2D> history = staticPositions;
        for (int i = 0 ; i<PLAYERS_MAX_NUM ; i++)
        {
            if (!_wm->ourRobot[i].isValid || !_agents[i]->isDummy())
                continue;
            int  temp;
            if (roles > 2)
            {
                Vector2D myPos = _knowledge.findNearestPositionToRobot(staticPositions,i);
                temp = history.indexOf(myPos);
                staticPositions.removeOne(myPos);
            }
            switch (roles)
            {
            case 6:
                switch (temp)
                {
                case 0:
                    _tlb->setRID(i);
                    _agents[i]->assignTactic(_tlb);
                    break;
                case 1:
                    _trb->setRID(i);
                    _agents[i]->assignTactic(_trb);
                    break;
                case 2:
                    _tcm->setRID(i);
                    _agents[i]->assignTactic(_tcm);
                    break;
                case 3:
                    _tlf->setRID(i);
                    _agents[i]->assignTactic(_tlf);
                    break;
                case 4:
                    _trf->setRID(i);
                    _agents[i]->assignTactic(_trf);
                    break;
                }
                break;
            case 5:
                switch (temp)
                {
                case 0:
                    _tlb->setRID(i);
                    _agents[i]->assignTactic(_tlb);
                    break;
                case 1:
                    _trb->setRID(i);
                    _agents[i]->assignTactic(_trb);
                    break;
                case 2:
                    _tcm->setRID(i);
                    _agents[i]->assignTactic(_tcm);
                    break;
                case 3:
                    _tcf->setRID(i);
                    _agents[i]->assignTactic(_tcf);
                    break;
                }
                break;
            case 4:
                switch (temp)
                {
                case 0:
                    _tlb->setRID(i);
                    _agents[i]->assignTactic(_tlb);
                    break;
                case 1:
                    _trb->setRID(i);
                    _agents[i]->assignTactic(_trb);
                    break;
                case 2:
                    _tcm->setRID(i);
                    _agents[i]->assignTactic(_tcm);
                    break;
                }
                break;
            case 3:
                switch(temp)
                {
                case 0:
                    _tlb->setRID(i);
                    _agents[i]->assignTactic(_tlb);
                    break;
                case 1:
                    _trb->setRID(i);
                    _agents[i]->assignTactic(_trb);
                    break;
                }
                break;
            case 2:
                _tcb->setRID(i);
                _agents[i]->assignTactic(_tcb);
                break;
            default :
                break;
            }
        }
        _firstTimeFlag = false;
    }
    else
    {
        if(_knowledge.countActiveAgents() != robotNum)
        {
            for (int cnt = 0 ; cnt < PLAYERS_MAX_NUM ; cnt++)
            {
                if (!_wm->ourRobot[cnt].isValid && !_agents[cnt]->isDummy())
                    _agents[cnt]->assignTactic(0);
            }
            robotNumChanged();
        }
    }

    return true;
}

void StrategyDefault::robotNumChanged()
{
    robotNum = _knowledge.countActiveAgents();
    if (_wm->ourRobot[GOALIE_ID].isValid)
    {
        _tg->setRID(GOALIE_ID);
        _agents[GOALIE_ID]->assignTactic(_tg);
        _knowledge.validGoalie = true;
    }
    else
    {
        _agents[GOALIE_ID]->assignTactic(0);
        _knowledge.validGoalie = false;
    }
    QList <Vector2D> staticPositions;
    int roles = _knowledge.countActiveRoles();
    if (roles > 2)
        for(int cnt = 1 ; cnt<roles ; cnt++)
            staticPositions.append(_wm->position(cnt,roles,_wm->ball.pos.loc, GameOn));
    QList <Vector2D> history = staticPositions;
    for (int i = 0 ; i<PLAYERS_MAX_NUM ; i++)
    {
        if (!_wm->ourRobot[i].isValid || i==GOALIE_ID)
            continue;
        if(hasValidTactic(i))
        {
            QList <QString> tempList;
            switch (roles)
            {
            case 6:
                tempList = _validTactics6;
                break;
            case 5:
                tempList = _validTactics5;
                break;
            case 4:
                tempList = _validTactics4;
                break;
            case 3:
                tempList = _validTactics3;
                break;
            }
            staticPositions.removeOne(history.at(tempList.indexOf(_agents[i]->tactic()->Name())-1));
            continue;
        }
    }
    for (int i = 0 ; i<PLAYERS_MAX_NUM ; i++)
    {
        if (!_wm->ourRobot[i].isValid || hasValidTactic(i))
            continue;
        int  temp;
        if (_knowledge.countActiveAgents() > 2)
        {
            Vector2D myPos = _knowledge.findNearestPositionToRobot(staticPositions,i);
            temp = history.indexOf(myPos);
            staticPositions.removeOne(myPos);
        }
        switch (roles)
        {
        case 6:
            switch (temp)
            {
            case 0:
                _tlb->setRID(i);
                _agents[i]->assignTactic(_tlb);
                break;
            case 1:
                _trb->setRID(i);
                _agents[i]->assignTactic(_trb);
                break;
            case 2:
                _tcm->setRID(i);
                _agents[i]->assignTactic(_tcm);
                break;
            case 3:
                _tlf->setRID(i);
                _agents[i]->assignTactic(_tlf);
                break;
            case 4:
                _trf->setRID(i);
                _agents[i]->assignTactic(_trf);
                break;
            }
            break;
        case 5:
            switch (temp)
            {
            case 0:
                _tlb->setRID(i);
                _agents[i]->assignTactic(_tlb);
                break;
            case 1:
                _trb->setRID(i);
                _agents[i]->assignTactic(_trb);
                break;
            case 2:
                _tcm->setRID(i);
                _agents[i]->assignTactic(_tcm);
                break;
            case 3:
                _tcf->setRID(i);
                _agents[i]->assignTactic(_tcf);
                break;
            }
            break;
        case 4:
            switch (temp)
            {
            case 0:
                _tlb->setRID(i);
                _agents[i]->assignTactic(_tlb);
                break;
            case 1:
                _trb->setRID(i);
                _agents[i]->assignTactic(_trb);
                break;
            case 2:
                _tcm->setRID(i);
                _agents[i]->assignTactic(_tcm);
                break;
            }
            break;
        case 3:
            switch(temp)
            {
            case 0:
                _tlb->setRID(i);
                _agents[i]->assignTactic(_tlb);
                break;
            case 1:
                _trb->setRID(i);
                _agents[i]->assignTactic(_trb);
                break;
            }
            break;
        case 2:
            _tcb->setRID(i);
            _agents[i]->assignTactic(_tcb);
            break;
        default :
            break;
        }
    }
}

bool StrategyDefault::hasValidTactic(int rid)
{
    if (_agents[rid]->isDummy())
        return false;
    if (_agents[rid]->tactic()->Name().compare(_tg->Name())==0)
        return true;
    QList <QString> myTactics;
    int roles = _knowledge.countActiveRoles();
    switch (roles)
    {
    case 6:
        myTactics = _validTactics6;
        break;
    case 5:
        myTactics = _validTactics5;
        break;
    case 4:
        myTactics = _validTactics4;
        break;
    case 3:
        myTactics = _validTactics3;
        break;
    default:
        break;

    }
    return myTactics.contains(_agents[rid]->tactic()->Name());
}

bool StrategyDefault::ExecuteStrategyEngine1()
{
    if(_knowledge.countActiveAgents()==0)
        return false;
    if (_firstTimeFlag)
    {
        if (_wm->ourRobot[GOALIE_ID].isValid)
        {
            _tg->setRID(GOALIE_ID);
            _agents[GOALIE_ID]->assignTactic(_tg);
            _knowledge.validGoalie = true;
        }
        else
            _knowledge.validGoalie = false;
        robotNum = _knowledge.countActiveAgents();
        QList <Vector2D> staticPositions;
        if (robotNum > 2)
            for(int cnt = 1 ; cnt<robotNum ; cnt++)
                staticPositions.append(_wm->position(cnt,robotNum,_wm->ball.pos.loc, GameOn));
        //switch (robotNum)
        //{
        //case 6:
        //for(int cnt = 1 ; cnt<staticPositions.count() ; cnt++)


        //}
    }
}
