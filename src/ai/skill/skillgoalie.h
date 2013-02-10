#ifndef SKILLGOALIE_H
#define SKILLGOALIE_H

#include <QObject>
#include "skill.h"

class SkillGoalie : public Skill
{
    Q_OBJECT
public:
    explicit SkillGoalie(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    bool SkillDone();
};

#endif // SKILLGOALIE_H
