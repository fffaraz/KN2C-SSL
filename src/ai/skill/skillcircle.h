#ifndef SKILLCIRCLE_H
#define SKILLCIRCLE_H

#include <QObject>
#include "skill.h"

class SkillCircle : public Skill
{
    Q_OBJECT
public:
    explicit SkillCircle(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    bool SkillDone();
    Vector2D center;
    float radius;
    Vector2D pointTo;
};

#endif // SKILLCIRCLE_H
