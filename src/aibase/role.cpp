#include "role.h"

Role::Role(QString name, QObject *parent) :
    QObject(parent),
    _name(name)
{
}
