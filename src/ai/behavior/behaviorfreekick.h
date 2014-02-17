#ifndef BEHAVIORFREEKICK_H
#define BEHAVIORFREEKICK_H

#define DEFAULT 0
#define SHOOT 1
#define PASS 2

#include "behavior.h"

#include "skill/skillgotoposition.h"
#include "skill/skillkickball.h"

#include "behavior/behaviorpass.h"
#include "behavior/behaviorshoot.h"
#include "behavior/behaviorgotostaticball.h"

class BehaviorFreeKick : public Behavior
{
    Q_OBJECT
public:
    BehaviorFreeKick(WorldModel* wm, Knowledge *kn, QObject *parent = 0, bool readSixFormation = false);
    bool execute(RobotCommand &rc);

    void setOur(bool our) { this->_our = our ; }
    void setDirect(bool direct) { this->_direct = direct; }

    bool doMoveOurFreeKick(RobotCommand &rc);
    bool doKickOurFreeKick(RobotCommand &rc);
    bool doMoveTheirFreeKick(RobotCommand &rc);

public:
    Position getKickPosition();
    Position getMovePosition();

private:
    bool _our;
    bool _direct;
    bool _readSixFormation;

    int _behavior;

private:
    SkillGotoPosition *_sgp;
    SkillKickBall *_skb;

    BehaviorPass *_bp;
    BehaviorShoot *_bs;
    BehaviorGoToStaticBall *_bgtsb;
};

#endif // BEHAVIORFREEKICK_H
