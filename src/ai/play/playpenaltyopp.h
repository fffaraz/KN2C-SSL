#ifndef PLAYPENALTYOPP_H
#define PLAYPENALTYOPP_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayPenaltyOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayPenaltyOpp(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();

private:

    TacticGoalie* _tg;
    RoleGoalie* _rg;

    TacticStop* _ts1;
    TacticStop* _ts2;
    TacticStop* _ts3;
    TacticStop* _ts4;
    TacticStop* _ts5;

};

#endif // PLAYPENALTYOPP_H
