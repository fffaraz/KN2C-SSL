#ifndef TACTICGOALIE_H
#define TACTICGOALIE_H

#include <QObject>
#include "tactic.h"
#include <limits>

class TacticGoalie : public Tactic
{
    Q_OBJECT
public:
    explicit TacticGoalie(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    bool doKick(RobotCommand &rc);
    bool doMove(RobotCommand &rc);

    bool doPlayOn(RobotCommand &rc);
    bool doOurIndirectFreeKick(RobotCommand &rc);
    bool doTheirIndirectFreeKick(RobotCommand &rc);
    bool doOurDirectFreeKick(RobotCommand &rc);
    bool doTheirDirectFreeKick(RobotCommand &rc);
    bool doStop(RobotCommand &rc);
    bool doOurPenalty(RobotCommand &rc);
    bool doTheirPenalty(RobotCommand &rc);
    bool doOurKickoff(RobotCommand &rc);
    bool doTheirKickoff(RobotCommand &rc);

private:
    SkillGotoPosition *_sgp;
    SkillKickBall *_skb;
    BehaviorPenalty *_bp;
    bool _tracePass;
    int _passDestination;
    double _lastDist;
};

#endif // TACTICGOALIE_H
