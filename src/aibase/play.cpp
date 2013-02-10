#include "play.h"

Play::Play(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _wm(wm),
    _sr(sr),
    _kn(kn)
{
}
