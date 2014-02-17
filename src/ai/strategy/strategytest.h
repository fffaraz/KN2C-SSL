#ifndef STRATEGYTEST_H
#define STRATEGYTEST_H

#include <QObject>
#include "strategy.h"
#include "skill.h"
#include "Skills.h"


class StrategyTest : public Strategy
{
    Q_OBJECT
public:
    explicit StrategyTest(WorldModel* wm, QMap<int,Agent*> &agents, QObject *parent = 0);
    bool ExecuteStrategyEngine();

private:
    Knowledge _knowledge;

signals:

public slots:

};

#endif // STRATEGYTEST_H
