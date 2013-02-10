#ifndef SKILLGOTOPOSITION_H
#define SKILLGOTOPOSITION_H

#include <QObject>
#include "skill.h"
#include "navigationdefault.h"

class SkillGotoPosition : public Skill
{
    Q_OBJECT
public:
    explicit SkillGotoPosition(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    void setPosition(const Position& Final, float Speed = 1);
    void setMaxDist(double maxdist) { _maxdist=maxdist; }
    bool SkillDone();

protected:
    Position _FinalPos;
    NavigationDefault _nav;
    float _Speed;
    double _maxdist;
};

#endif // SKILLGOTOPOSITION_H
