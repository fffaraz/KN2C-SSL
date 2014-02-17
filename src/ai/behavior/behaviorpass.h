#ifndef BEHAVIORPASS_H
#define BEHAVIORPASS_H

#include "behavior.h"
#include "skill/skillkickball.h"

class BehaviorPass
        : public Behavior
{
    Q_OBJECT

public:
    explicit BehaviorPass(WorldModel *wm, Knowledge *kn, QObject *parent = 0);
    virtual bool execute(RobotCommand &rc);
    bool canPass(Vector2D &target, float &targetAngle, int &targetId);

    Vector2D receiver();
    float receiverAngle();
    int receiverRid();

private:
    SkillKickBall *_skb;

    Vector2D _receiver;
    float _receiverAngle;
    int _receiverRid;
};

#endif // BEHAVIORPASS_H
