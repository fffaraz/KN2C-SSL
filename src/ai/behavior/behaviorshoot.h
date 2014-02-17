#ifndef BEHAVIORSHOOT_H
#define BEHAVIORSHOOT_H

#include "behavior.h"
#include "skill/skillkickball.h"

class BehaviorShoot
        : public Behavior
{
public:
    explicit BehaviorShoot(WorldModel *wm, Knowledge *kn, QObject *parent = 0);
    virtual bool execute(RobotCommand &rc);
    bool canShoot(Vector2D &target, float &targetAngle);

    Vector2D target();
    float targetAngle();

private:
    SkillKickBall *_skb;

    Vector2D _target;
    float _targetAngle;
};

#endif // BEHAVIORSHOOT_H
