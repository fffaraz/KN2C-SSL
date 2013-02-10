#ifndef TACTICNULL_H
#define TACTICNULL_H

#include <QObject>
#include "tactic.h"
#include "skills.h"

class TacticNull : public Tactic
{
    Q_OBJECT
public:
    explicit TacticNull(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();

private:
    Skill* _skillnull;

signals:

public slots:

};

#endif // TACTICNULL_H
