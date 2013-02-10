#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QObject>
#include "position.h"
#include "agent.h"
#include "worldmodel.h"

class Navigation : public QObject
{
    Q_OBJECT
public:
    explicit Navigation(WorldModel* wm, QString name, QObject *parent = 0);
    QString Name() { return _name; }
    virtual bool execute(int rid, Position FinalPos, Position& TargetPos)=0;
protected:
    QString _name;
    WorldModel* _wm;

signals:

public slots:

};

#endif // NAVIGATION_H
