#ifndef PLAYTEST_H
#define PLAYTEST_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "tactics.h"

class PlayTest : public Play
{
    Q_OBJECT
public:
    explicit PlayTest(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();
private:
    TacticTest* _tt;
    TacticAttack* _ta;
};

#endif // PLAYTEST_H
