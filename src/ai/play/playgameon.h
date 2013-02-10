#ifndef PLAYGAMEON_H
#define PLAYGAMEON_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayGameOn : public Play
{
    Q_OBJECT
public:
    explicit PlayGameOn(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();

private:

    TacticGoalie* _tg;
    RoleGoalie* _rg;

    TacticDefend* _td1;
    TacticDefend* _td2;
    RoleDefender* _rd;

    TacticAttack* _ta;

    TacticBlock* _tb1;
    TacticBlock* _tb2;

};

#endif // PLAYGAMEON_H
