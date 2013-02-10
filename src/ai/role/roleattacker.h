#ifndef ROLEATTACKER_H
#define ROLEATTACKER_H

#include <QObject>
#include "role.h"

class RoleAttacker : public Role
{
    Q_OBJECT
public:
    explicit RoleAttacker(QObject *parent = 0);

signals:

public slots:

};

#endif // ROLEATTACKER_H
