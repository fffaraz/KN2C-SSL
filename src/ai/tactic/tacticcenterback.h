#ifndef TACTICCENTERBACK_H
#define TACTICCENTERBACK_H

#include <QObject>
#include "tactic.h"

class TacticCenterBack : public Tactic
{
    Q_OBJECT
public:
    explicit TacticCenterBack(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
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
    BehaviorFreeKick * _bfk;
    BehaviorKickoff *_bk;
    BehaviorPenalty *_bp;

    bool _avoidance;

};

#endif // TACTICCENTERBACK_H
