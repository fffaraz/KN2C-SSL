#ifndef PLAYNULL_H
#define PLAYNULL_H

#include <QObject>
#include "play.h"
#include "roles.h"

class PlayNull : public Play
{
    Q_OBJECT
public:
    explicit PlayNull(WorldModel* wm, StrategyResult* sr, Knowledge* kn, QObject *parent = 0);
    virtual bool EnterCondition();
    virtual bool ExecutePlayEngine();
};

#endif // PLAYNULL_H
