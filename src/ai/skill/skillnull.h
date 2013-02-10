#ifndef SKILLNULL_H
#define SKILLNULL_H

#include <QObject>
#include "skill.h"

class SkillNull : public Skill
{
    Q_OBJECT
public:
    explicit SkillNull(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    bool SkillDone();
};

#endif // SKILLNULL_H
