#ifndef TACTICCENTERFORWARD_H
#define TACTICCENTERFORWARD_H

#include <QObject>
#include "tactic.h"

class TacticCenterForward : public Tactic
{
    Q_OBJECT
public:
    explicit TacticCenterForward(WorldModel* wm , Knowledge* kn , QObject* parent=0);
    bool doMove(RobotCommand &rc);
    bool doKick(RobotCommand &rc);

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
    BehaviorFreeKick *_bfk;
    BehaviorStop *_bs;
    BehaviorKickoff* _bk;
    BehaviorPenalty *_bp;
};

#endif // TACTICCENTERFORWARD_H
