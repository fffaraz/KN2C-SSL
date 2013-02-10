#ifndef PLAYKICKOFFOUR_H
#define PLAYKICKOFFOUR_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayKickoffOur : public Play
{
    Q_OBJECT
public:
    explicit PlayKickoffOur(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();
    void setCanKick(bool ck) { _cankick=ck; }

private:
    bool _cankick;

    TacticGoalie*  _tg;
    RoleGoalie*    _rg;

    TacticDefend*  _td1;
    TacticDefend*  _td2;
    RoleDefender*  _rd;

    TacticStop* _ts;

    TacticBlock* _tb1;
    TacticBlock* _tb2;

    TacticAttack* _ta;


    TacticStop*    _ts1;
    TacticStop*    _ts2;
    TacticStop*    _ts3;

    bool BeforeNormal();
    bool AfterNormal();

};

#endif // PLAYKICKOFFOUR_H
