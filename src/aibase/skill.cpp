#include "skill.h"

Skill::Skill(WorldModel *wm, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _rid(-1),
    _wm(wm)
{

}
