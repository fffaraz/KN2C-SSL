#ifndef SKILLGOALIEPENALTY_H
#define SKILLGOALIEPENALTY_H

#include <QObject>
#include "skill.h"

class SkillGoaliePenalty : public Skill
{
    Q_OBJECT
public:
    explicit SkillGoaliePenalty(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    bool SkillDone();
};
//////

#endif // SKILLGOALIEPENALTY_H
