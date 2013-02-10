#ifndef PLAY_H
#define PLAY_H

#include <QObject>
#include "worldmodel.h"
#include "knowledge.h"
#include "strategyresult.h"
#include "tactics.h"


class Play : public QObject
{
    Q_OBJECT
public:
    explicit Play(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QString name, QObject *parent = 0);
    QString Name() { return _name; }
    virtual bool EnterCondition()=0;
    virtual bool ExecutePlayEngine()=0;

protected:
    QString _name;
    WorldModel* _wm;
    StrategyResult* _sr;
    Knowledge* _kn;

};

#endif // PLAY_H
