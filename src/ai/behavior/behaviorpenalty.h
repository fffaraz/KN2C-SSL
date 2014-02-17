#ifndef BEHAVIORPENALTY_H
#define BEHAVIORPENALTY_H

#include "behavior.h"
#include "Skills.h"
#include "constants.h"

class BehaviorPenalty
        : public Behavior
{
public:
    explicit BehaviorPenalty(WorldModel *wm, Knowledge *kn, QObject *parent = 0);
    virtual bool execute(RobotCommand &rc);
    void isOur(bool _our){this->_our=_our;}
private:
    SkillGotoPosition *_sgp;
    SkillKickBall *_skb;
    SkillTurnToAngle *_sta;
    bool GoBehindBall(RobotCommand &rc);
    bool GoBehindBall2(RobotCommand &rc);
    bool TurnToGoalCorner(RobotCommand &rc);
    bool KickBall(RobotCommand &rc);
    bool _our;

};

#endif // BEHAVIORPENALTY_H
