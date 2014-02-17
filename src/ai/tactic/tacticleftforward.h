#ifndef TACTICLEFTFORWARD_H
#define TACTICLEFTFORWARD_H

#include <QObject>
#include "tactic.h"

class TacticLeftForward : public Tactic
{
    Q_OBJECT

public:
    explicit TacticLeftForward(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
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
    BehaviorFreeKick *_bfk;
    BehaviorStop* _bs;
    BehaviorKickoff* _bk;
    SkillGotoPosition *_sgp;
    SkillKickBall *_skb;
    BehaviorPenalty *_bp;

signals:

public slots:
};

#endif // TACTICLEFTFORWARD_H
