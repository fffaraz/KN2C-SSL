#include "playhalt.h"

PlayHalt::PlayHalt(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayHalt", parent)
{
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
        _tactic[i] = new TacticNull(wm, kn, this);
}

bool PlayHalt::EnterCondition()
{
    if(_wm->cmgs.canMove()==false)
    //if(_wm->gs == STATE_Halt)
        return true;
    else
        return false;
}

bool PlayHalt::ExecutePlayEngine()
{
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        _tactic[i]->setRID(i);
        _sr->tactics[i] = _tactic[i];
        _sr->useSkill[i] = 0;
    }
    return true;
}
