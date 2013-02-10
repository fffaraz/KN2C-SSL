#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
#include <QMap>
#include "worldmodel.h"
#include "knowledge.h"
#include "strategyresult.h"

class Strategy : public QObject
{
    Q_OBJECT
public:
    explicit Strategy(WorldModel* wm, QString name, QObject *parent = 0);
    QString Name() { return _name; }
    Skill* getSkill(int rid);

    virtual bool ExecuteStrategyEngine()=0;

protected:
    QString _name;
    WorldModel* _wm;
    StrategyResult _result;

signals:

public slots:

};

#endif // STRATEGY_H
