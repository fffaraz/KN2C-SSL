#ifndef ROLEDEFENDER_H
#define ROLEDEFENDER_H

#include <QObject>
#include "role.h"

class RoleDefender : public Role
{
    Q_OBJECT
public:
    explicit RoleDefender(QObject *parent = 0);

signals:

public slots:

};

#endif // ROLEDEFENDER_H
