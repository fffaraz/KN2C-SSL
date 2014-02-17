#ifndef TACTICRIGHTFORWARD_H
#define TACTICRIGHTFORWARD_H

#include<QObject>
#include "tactic.h"

class TacticRightForward : public Tactic
{
    Q_OBJECT
public:
    explicit TacticRightForward(WorldModel* wm, Knowledge* kn,QObject *parent = 0);
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
    BehaviorStop *_bs;
    BehaviorFreeKick *_bfk;
    BehaviorKickoff* _bk;
    BehaviorPenalty *_bp;


signals:

public slots:

};

#endif // TACTICRIGHTFORWARD_H
