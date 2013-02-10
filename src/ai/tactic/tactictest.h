#ifndef TACTICTEST_H
#define TACTICTEST_H

#include <QObject>
#include "tactic.h"
#include "skills.h"

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();

private:
    SkillGotoPosition* _sp;
    SkillWait* _sw;
    int _state;
    Position _p1;
    Position _p2;

signals:

public slots:

};

#endif // TACTICTEST_H
