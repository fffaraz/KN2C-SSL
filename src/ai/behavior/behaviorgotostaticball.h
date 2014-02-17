#ifndef BEHAVIORGOTOSTATICBALL_H
#define BEHAVIORGOTOSTATICBALL_H

#include "behavior.h"
#include "skill/skillgotoposition.h"

class BehaviorGoToStaticBall
        : public Behavior
{
public:
    explicit BehaviorGoToStaticBall(WorldModel *wm, Knowledge *kn, QObject *parent = 0);
    virtual bool execute(RobotCommand &rc);

    void setBodyAngle(float bodyAngle) { _bodyAngle = bodyAngle; }
    GoToStaticBallState state() { return _state; }

private:
    GoToStaticBallState getState(Position& target);

private:
    float _bodyAngle;
    int _waitStart; // wait start time in second

    GoToStaticBallState _state;
private:
    SkillGotoPosition *_sgp;
};

#endif // BEHAVIORGOTOSTATICBALL_H
