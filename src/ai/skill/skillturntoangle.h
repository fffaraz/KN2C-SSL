#ifndef SKILLTURNTOANGLE_H
#define SKILLTURNTOANGLE_H

#include "skill.h"

class SkillTurnToAngle
        : public Skill
{
public:
    SkillTurnToAngle(WorldModel* wm, QObject *parent = 0);

public:
    bool execute(RobotCommand& rc);
    bool done();

    void setTarget(float target) { _target = target; }

private:
    float _target;
    bool _done;

};

#endif // SKILLTURNTOANGLE_H
