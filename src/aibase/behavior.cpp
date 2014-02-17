#include "behavior.h"

Behavior::Behavior(WorldModel *wm, Knowledge *kn, QString name, QObject *parent)
    : _wm (wm),
      _kn (kn),
      _name (name),
      _rid (-1)
{
}
