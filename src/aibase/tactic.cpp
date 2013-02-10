#include "tactic.h"

Tactic::Tactic(WorldModel *wm, Knowledge *kn, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _rid(-1),
    _wm(wm),
    _kn(kn)
{

}

