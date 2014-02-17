#ifndef TACTICRIGHTMIDFIELDER_H
#define TACTICRIGHTMIDFIELDER_H

#include <QObject>
#include "tactic.h"

class TacticRightMidfielder : public Tactic
{
    Q_OBJECT
public:
    explicit TacticRightMidfielder(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
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
    BehaviorFreeKick *_bfk;
    BehaviorPenalty *_bp;

signals:

public slots:

};

#endif // TACTICRIGHTMIDFIELDER_H
