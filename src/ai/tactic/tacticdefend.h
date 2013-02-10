#ifndef TACTICDEFEND_H
#define TACTICDEFEND_H

#include <QObject>
#include "tactic.h"
#include "skills.h"

class TacticDefend : public Tactic
{
    Q_OBJECT
public:
    explicit TacticDefend(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();
    void setTotalDef(int td) { _total_def=td; }
    void setMyDef(int md) { _my_def=md; }
    QMap<int,int> defs;

private:
    SkillGotoPosition* _skill;
    int _total_def;
    int _my_def;

signals:

public slots:

};

#endif // TACTICDEFEND_H
