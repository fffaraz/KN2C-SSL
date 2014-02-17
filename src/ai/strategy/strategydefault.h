#ifndef STRATEGYDEFAULT_H
#define STRATEGYDEFAULT_H

#include <QObject>
#include "strategy.h"
#include "skill.h"
#include "Skills.h"
#include "formationparser.h"
#include "navigationdefault.h"
#include "Tactics.h"


class StrategyDefault : public Strategy
{
    Q_OBJECT
public:
    explicit StrategyDefault(WorldModel* wm, QMap<int,Agent*> &agents, QObject *parent = 0);
    bool ExecuteStrategyEngine();
    bool ExecuteStrategyEngine1();

    void robotNumChanged();

    int robotNum;

    bool hasValidTactic(int rid);

private:
    Knowledge _knowledge;
    bool _firstTimeFlag ;

    TacticGoalie* _tg;
    TacticCenterBack* _tcb;
    TacticLeftBack* _tlb;
    TacticRightBack* _trb;
    TacticCenterMidfielder* _tcm;
    TacticLeftMidfielder* _tlm;
    TacticRightMidfielder* _trm;
    TacticCenterForward* _tcf;
    TacticLeftForward* _tlf;
    TacticRightForward* _trf;
    QList <QString> _validTactics6;
    QList <QString> _validTactics5;
    QList <QString> _validTactics4;
    QList <QString> _validTactics3;

signals:

public slots:

};

#endif // STRATEGYDEFAULT_H
