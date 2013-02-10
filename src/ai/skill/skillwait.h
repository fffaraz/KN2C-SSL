#ifndef SKILLWAIT_H
#define SKILLWAIT_H

#include <QObject>
#include <QTime>
#include "skill.h"

class SkillWait : public Skill
{
    Q_OBJECT
public:
    explicit SkillWait(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    void setPosition(const Position& Final);
    bool SkillDone();
    void ResetTime();
    void setTime(int time) { _time=time; }

private:
    Position _Pos;
    QTime _qtime;
    int _elapsed;
    int _time;
};

#endif // SKILLWAIT_H
