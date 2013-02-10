#ifndef ROLENULL_H
#define ROLENULL_H

#include <QObject>
#include "role.h"

class RoleNull : public Role
{
    Q_OBJECT
public:
    explicit RoleNull(QObject *parent = 0);

signals:

public slots:

};

#endif // ROLENULL_H
