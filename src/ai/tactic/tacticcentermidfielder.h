#ifndef TACTICCENTERMIDFIELDER_H
#define TACTICCENTERMIDFIELDER_H

#include <QObject>
#include "tactic.h"

class TacticCenterMidfielder : public Tactic
{
    Q_OBJECT
public:
    explicit TacticCenterMidfielder(WorldModel* wm,Knowledge* kn, QObject* parent=0);
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
    int index;

private:
    SkillGotoPosition *_sgp;
    SkillKickBall *_skb;
    BehaviorFreeKick *_bfk;
    BehaviorStop *_bs;
    BehaviorKickoff *_bk;
    BehaviorPenalty *_bp;
};

#endif // TACTICCENTERMIDFIELDER_H
