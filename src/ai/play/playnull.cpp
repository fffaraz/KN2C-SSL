#include "playnull.h"

PlayNull::PlayNull(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayNull", parent)
{
}

bool PlayNull::EnterCondition()
{
    return true;
}

bool PlayNull::ExecutePlayEngine()
{
    return false;
}
