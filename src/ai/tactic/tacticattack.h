#ifndef TACTICATTACK_H
#define TACTICATTACK_H

#include <QObject>
#include "tactic.h"
#include "skills.h"

class TacticAttack : public Tactic
{
    Q_OBJECT
public:
    explicit TacticAttack(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();

private:
    SkillKick* _kick;


};

#endif // TACTICATTACK_H
