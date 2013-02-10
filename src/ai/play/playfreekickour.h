#ifndef PLAYFREEKICKOUR_H
#define PLAYFREEKICKOUR_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayFreeKickOur : public Play
{
    Q_OBJECT
public:
    explicit PlayFreeKickOur(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();

private:

    TacticGoalie* _tg;
    RoleGoalie* _rg;

    TacticDefend* _td1;
    TacticDefend* _td2;
    TacticDefend* _td3;
    RoleDefender* _rd;

    TacticAttack* _ta;
    TacticBlock* _tb;

    TacticStop*    _ts1;
    TacticStop*    _ts2;
    TacticStop*    _ts3;
};

#endif // PLAYFREEKICKOUR_H
