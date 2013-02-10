#ifndef TACTICGOALIE_H
#define TACTICGOALIE_H

#include <QObject>
#include "tactic.h"
#include "skills.h"

class TacticGoalie : public Tactic
{
    Q_OBJECT
public:
    explicit TacticGoalie(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();
    void setPenalty(bool p) { _penalty=p; }


private:
    SkillGoalie* _skill;
    SkillGoaliePenalty* _skillp;
    bool _penalty;
};

#endif // TACTICGOALIE_H
