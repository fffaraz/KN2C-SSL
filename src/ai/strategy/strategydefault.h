#ifndef STRATEGYDEFAULT_H
#define STRATEGYDEFAULT_H

#include <QObject>
#include "strategy.h"


class StrategyDefault : public Strategy
{
    Q_OBJECT
public:
    explicit StrategyDefault(WorldModel* wm, QObject *parent = 0);
    bool ExecuteStrategyEngine();

private:
    QList<Play*> _playList;
    Knowledge _knowledge;
    void printResult();

signals:

public slots:

};

#endif // STRATEGYDEFAULT_H
