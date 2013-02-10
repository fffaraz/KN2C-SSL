#ifndef PLAYHALT_H
#define PLAYHALT_H

#include <QObject>
#include "play.h"
#include "roles.h"
#include "knowledge.h"

class PlayHalt : public Play
{
    Q_OBJECT
public:
    explicit PlayHalt(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();

private:
    TacticNull* _tactic[PLAYERS_MAX_NUM];

};

#endif // PLAYHALT_H
