#include "navigation.h"

Navigation::Navigation(WorldModel *wm, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _wm(wm)
{
}
