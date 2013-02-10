#include "strategydefault.h"
#include "plays.h"

StrategyDefault::StrategyDefault(WorldModel *wm, QObject *parent) :
    Strategy(wm, "StrategyDefault", parent),
    _knowledge(wm, &_result)
{
    // Creating and setting parameters of used plays in this strategy
    PlayNull* playnull = new PlayNull(wm, &_result, &_knowledge, this);
    PlayStop* playstop = new PlayStop(wm, &_result, &_knowledge, this);
    PlayHalt* playhalt = new PlayHalt(wm, &_result, &_knowledge, this);
    PlayFreeKickOpp* playfreekickopp =  new PlayFreeKickOpp(wm, &_result, &_knowledge, this);
    PlayFreeKickOur* playfreekickour =  new PlayFreeKickOur(wm, &_result, &_knowledge, this);
    PlayGameOn* playgameon = new PlayGameOn(wm, &_result, &_knowledge, this);
    PlayKickoffOpp* playkickoffopp = new PlayKickoffOpp(wm, &_result, &_knowledge, this);
    PlayKickoffOur* playkickoffour0 = new PlayKickoffOur(wm, &_result, &_knowledge, this);
    playkickoffour0->setCanKick(false);
    PlayKickoffOur* playkickoffour1 = new PlayKickoffOur(wm, &_result, &_knowledge, this);
    playkickoffour1->setCanKick(true);
    PlayPenaltyOpp* playpenaltyopp = new PlayPenaltyOpp(wm, &_result, &_knowledge, this);
    PlayPenaltyOur* playpenaltyour0 = new PlayPenaltyOur(wm, &_result, &_knowledge, this);
    playpenaltyour0->setCanKick(false);
    PlayPenaltyOur* playpenaltyour1 = new PlayPenaltyOur(wm, &_result, &_knowledge, this);
    playpenaltyour1->setCanKick(true);

    Play* plays[12];
    plays[0] = playnull;
    //plays[0] = new PlayTest(wm, &_result, &_knowledge, this);
    plays[1] = playstop;
    plays[2] = playhalt;
    plays[3] = playfreekickopp;
    plays[4] = playfreekickour;
    plays[5] = playgameon;
    plays[6] = playkickoffopp;
    plays[7] = playkickoffour0;
    plays[8] = playkickoffour1;
    plays[9] = playpenaltyopp;
    plays[10] = playpenaltyour0;
    plays[11] = playpenaltyour1;

    for(int i=0; i<12; i++)
        _playList.append(plays[i]);
}

bool StrategyDefault::ExecuteStrategyEngine()
{
    printResult();

    // 1 : find play
    bool playsEnterCondition[PLAYERS_MAX_NUM];
    int playsCounter=0;
    int lastplay=0;
    //qDebug() << "-------------------";
    for(int i=0; i<_playList.count(); i++)
    {
        playsEnterCondition[i]=_playList[i]->EnterCondition();
        //qDebug() << i << _playList[i]->Name() << playsEnterCondition[i];
        if(playsEnterCondition[i])
        {
            lastplay=i;
            playsCounter++;
        }
    }
    //qDebug() << "-------------------";
    if(playsCounter==2) _result.play=_playList[lastplay];
    else if(playsCounter==1) _result.play=_playList[0];
    else qDebug() << "~~~ playsCounter!=2 ~~~";
    //qDebug() << "Play: " << _result.play->Name();

    // 2 : execute play engine
    return _result.play->ExecutePlayEngine();
}

void StrategyDefault::printResult()
{
    qDebug() << "+++++++++++++++++++++++++++++++++++++";
    qDebug() << "PLAY: " << _result.play->Name();
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        if(!_wm->ourRobot[i].isValid) continue;
        qDebug() << "---------------------------------";
        qDebug() << "R" << i << ":: " <<
                    _result.roles[i]->Name() << " "
                 << _result.tactics[i]->Name() << " "
                 << getSkill(i)->Name() << " "
                 << _result.skills[i]->Name() << " "
                 << QString::number((int)_result.useSkill[i]) << " "
                 << QString::number(_result.tactics[i]->RID());
    }

}
