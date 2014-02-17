#ifndef SKILLTURNTOPOINT_H
#define SKILLTURNTOPOINT_H
#include <QObject>
#include "skill.h"

class SkillTurnToPoint : public Skill
{
    Q_OBJECT
public:
    SkillTurnToPoint(WorldModel* wm, QObject *parent = 0);

public:
    bool execute(RobotCommand& rc);
    bool done();

    void setTarget(Vector2D target) { _target = target; }

private:
    Vector2D _target;
    bool _done;

};
#endif // SKILLTURNTOPOINT_H
