#ifndef PLAYKICKOFFOPP_H
#define PLAYKICKOFFOPP_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayKickoffOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayKickoffOpp(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();

private:
    TacticGoalie*  _tg;
    RoleGoalie*    _rg;

    TacticDefend*  _td1;
    TacticDefend*  _td2;
    RoleDefender*  _rd;

    TacticBlock* _tb1;
    TacticBlock* _tb2;

    TacticStop* _ts;

};

#endif // PLAYKICKOFFOPP_H
