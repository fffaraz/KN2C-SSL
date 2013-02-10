#ifndef PLAYPENALTYOUR_H
#define PLAYPENALTYOUR_H

#include <QObject>
#include "play.h"
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayPenaltyOur : public Play
{
    Q_OBJECT
public:
    explicit PlayPenaltyOur(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();
    void setCanKick(bool ck) { _cankick=ck; }

private:
    bool _cankick;

    TacticAttack* _ta;

    TacticStop* _ts1;
    TacticStop* _ts2;
    TacticStop* _ts3;
    TacticStop* _ts4;
    TacticStop* _ts5;
    TacticStop* _ts6;
};

#endif // PLAYPENALTYOUR_H
