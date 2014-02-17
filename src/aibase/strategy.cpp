#include "strategy.h"

Strategy::Strategy(WorldModel *wm, QMap<int, Agent *> &agents, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _wm(wm),
    _agents(agents)
{

}
