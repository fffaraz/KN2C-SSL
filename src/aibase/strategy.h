#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
#include <QMap>
#include "worldmodel.h"
#include "knowledge.h"
#include "agent.h"

class Strategy : public QObject
{
    Q_OBJECT
public:
    explicit Strategy(WorldModel* wm, QMap<int,Agent*> &agents, QString name, QObject *parent = 0);
    QString Name() { return _name; }

    virtual bool ExecuteStrategyEngine()=0;

protected:
    QString _name;
    WorldModel* _wm;
    QMap<int,Agent*> &_agents;

signals:

public slots:

};

#endif // STRATEGY_H
